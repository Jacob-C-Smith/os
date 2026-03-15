const std = @import("std");

pub fn build(b: *std.Build) !void {
    // Gather options and common parts
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});
    const c_flags = &.{ "-Wall", "-Wextra", "-std=c23" };
    const install_step = b.getInstallStep();

    // Create the boot module
    const boot_mod = b.createModule(.{
        .root_source_file = b.path("src/arch/x86/boot.zig"),

        .target = target,
        .optimize = optimize,

        .sanitize_c = .off,
    });
    boot_mod.addIncludePath(b.path("include/"));

    // Gather all the source files in src/
    // Note: So its not wise to use `std.Build.pathAtRoot` but ehhhh, not much else we can do
    var src_dir = try std.fs.cwd().openDir(b.pathFromRoot("src/"), .{
        .iterate = true,
        .access_sub_paths = true,
        .no_follow = true,
    });
    var src_walker = try src_dir.walk(b.allocator);
    defer src_walker.deinit();
    while (try src_walker.next()) |entry| {
        // Check if this is a c file
        const entry_ext = std.fs.path.extension(entry.basename);
        if (entry.kind != .file or !std.mem.eql(u8, entry_ext, ".c")) {
            continue;
        }

        // Add the source file to be compiled
        boot_mod.addCSourceFile(.{
            .file = b.path(b.pathJoin(&.{ "src", entry.path })),
            .language = .c,
            .flags = c_flags,
        });
    }

    // Create the kernel executable
    const kernel_exe = b.addExecutable(.{
        .name = "os",
        .root_module = boot_mod,
    });
    kernel_exe.setLinkerScript(b.path("src/arch/x86/linker.ld"));

    // Install the kernel
    const kernel_install = b.addInstallArtifact(kernel_exe, .{});
    install_step.dependOn(&kernel_install.step);

    // Add a failure if the kernel doesn't support the target
    switch (target.result.cpu.arch) {
        .x86, .x86_64 => {},
        else => kernel_exe.step.dependOn(&b.addFail("Unsupported target architecture!").step),
    }

    // Cleanup step
    const clean_step = b.step("clean", "Cleanup zig cache and zig-out directories");
    clean_step.dependOn(&b.addRemoveDirTree(b.path(".zig-cache")).step);
    clean_step.dependOn(&b.addRemoveDirTree(b.path("zig-out")).step);
}
