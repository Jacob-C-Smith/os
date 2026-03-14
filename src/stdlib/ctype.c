// header file
#include <ctype.h>
	
char _digits[UCHAR_MAX] = 
{
    ['0'] = 1,
    ['1'] = 1,
    ['2'] = 1,
    ['3'] = 1,
    ['4'] = 1,
    ['5'] = 1,
    ['6'] = 1,
    ['7'] = 1,
    ['8'] = 1,
    ['9'] = 1
};

// Digits
// This is a set of whole numbers { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }.

// Hexadecimal digits
// This is the set of { 0 1 2 3 4 5 6 7 8 9 A B C D E F a b c d e f }.

// Lowercase letters
// This is a set of lowercase letters { a b c d e f g h i j k l m n o p q r s t u v w x y z }.

// Uppercase letters
// This is a set of uppercase letters {A B C D E F G H I J K L M N O P Q R S T U V W X Y Z }.

// Letters
// This is a set of lowercase and uppercase letters.

// Alphanumeric characters This is a set of Digits, Lowercase letters and Uppercase letters.

// Punctuation characters
// This is a set of ! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _ ` { | } ~
	
// Graphical characters
// This is a set of Alphanumeric characters and Punctuation characters.

// Space characters 
// This is a set of tab, newline, vertical tab, form feed, carriage return, and space.



int isdigit ( int c ) { return _digits[c]; }