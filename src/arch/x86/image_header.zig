//!
//! Kernel image header formats
//!
const std = @import("std");
const builtin = @import("builtin");
const target_endian = builtin.cpu.arch.endian();

/// Image header
pub const ImageHeader = union(enum) {
    multiboot2: multiboot2.Config,

    /// Generates the bytes for the header
    pub fn generate(this: @This()) []const u8 {
        return switch (this) {
            .multiboot2 => |x| x.generate(),
        };
    }
};

/// Mulitboot2 compliant header
pub const multiboot2 = struct {
    /// Configuration for the header
    pub const Config = struct {
        /// What tags to include in the header
        tags: []header.Tag.Payload,

        /// Generates a multiboot2 header
        pub fn generate(this: @This()) []const u8 {
            return header.generate(this.tags) catch @panic("Ran out of multiboot2 header space!");
        }
    };

    /// Header namespace
    pub const header = struct {
        /// Maximum allowed size of the multiboot2 header
        const max_header_len: usize = 4096;

        /// Builds a multiboot2 header and returns the data
        pub fn generate(comptime tags: []const Tag.Payload) ![]const u8 {
            // Initialize the writer
            var buffer: [max_header_len]u8 = undefined;
            var writer = std.io.Writer.fixed(&buffer);

            // Write the header
            try writer.writeStruct(Header.init(), target_endian);

            // Write each tag and sentinal
            for (tags) |tag| {
                switch (tag) {
                    inline else => |x| {
                        try writer.writeStruct(x.tag(), target_endian);
                        try writer.write(x.payload());
                    },
                }
            }
            try writer.writeStruct(Tag.sentinal, target_endian);

            // Finalize the buffer and return
            const final = buffer[0..writer.end].*;
            return &final;
        }

        /// Multiboot2 header tag
        pub const Tag = extern struct {
            type: Type,
            flags: u16,
            size: u32,

            /// Sentinal type of the multiboot header
            pub const sentinal = @This(){
                .type = .sentinal,
                .flags = 0,
                .size = 8,
            };

            /// What type of tag we are
            pub const Type = enum(u16) {
                sentinal = 0,
                mbi_tag_types = 1,
            };

            /// Compile time tag information
            pub const Payload = union(Type) {
                /// Internal sentinal value
                sentinal: void,

                /// Tag types request tag
                mbi_tag_types: struct {
                    optional: bool,
                    requested: []const u32,

                    /// Gets the raw tag flags as a u16
                    fn flags(comptime this: @This()) u16 {
                        return @intFromBool(this.optional);
                    }

                    /// Gets the associated tag data
                    fn payload(comptime this: @This()) []const u8 {
                        var data: [this.requested.len * 4]u8 = undefined;
                        for (this.requested, 0..) |tag_type, tag_idx| {
                            std.mem.writeInt(
                                u32,
                                data[tag_idx * 4 .. tag_idx * 4 + 4],
                                tag_type,
                                .little,
                            );
                        }
                        const final = data;
                        return &final;
                    }
                },

                /// Gets the payload tag
                pub fn tag(this: @This()) Tag {
                    return switch (this) {
                        .sentinal => @compileError("Sentinal values aren't meant to be used"),
                        inline else => |x| .{
                            .type = std.meta.activeTag(x),
                            .flags = x.flags(),
                            .size = @sizeOf(Tag) + x.payload().len,
                        },
                    };
                }

                /// Gets the payload data
                pub fn payload(this: @This()) []const u8 {
                    return switch (this) {
                        .sentinal => @compileError("Sentinal values aren't meant to be used"),
                        inline else => |x| x.payload(),
                    };
                }
            };
        };

        /// Header present at start of kernel image
        pub const Header = extern struct {
            magic: u32 = 0xe85250d6,
            architecture: Arch,
            header_length: u32,
            checksum: u32,

            /// Builds the header
            pub fn init() @This() {
                var this = @This(){
                    .architecture = .fromArch(builtin.cpu.arch),
                    .header_length = @sizeOf(@This()),
                    .checksum = 0,
                };
                this.checksum = this.magic + @intFromEnum(this.architecture) + this.header_length;
                this.checksum = @bitCast(-@as(i32, @bitCast(this.checksum)));
                return this;
            }

            /// Architecture identifier
            pub const Arch = enum(u32) {
                i386 = 0,
                mips = 4,

                /// Generates an architecture identifier from an architecture
                pub fn fromArch(arch: std.Target.Cpu.Arch) @This() {
                    return switch (arch) {
                        .x86, .x86_64 => .i386,
                        else => @compileError("Unsupported architecture"),
                    };
                }
            };
        };
    };
};
