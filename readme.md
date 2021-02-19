# Roadmap of making a new language

## Lexer

A lexer takes in the language and scans through it. It appropriately takes out lexemes from the input code and assigns them the correct tokens as decided by the language maker. These tokens are then used in the syntactical analysis of the language.

## How to construct a lexer ?

With respect to this project, for the alpino language, we have a driver code that scans through the input program and appropriately according to some rules seperates out the lexemes. These lexems are then sent to the lexer which decides the token for the received lexeme and sends it back to the driver which then prints it out.

## Step by step lexing process

* Driver starts scanning the input program
* Driver has a logic according to which it finds that the lexeme starts here and ends here and then it sends it to the lexer.
* The lexer receives the lexeme and finds the appropriate token and returns it back to the driver.
* The driver prints the token and the line number.

## Structure of the lexer

### input.h

It contains the input alpino code to be split into tokens.

### driver.c

This code scans through the input code and according to the character found, calls the appropriate lexer method of the lexer.h file.

### lexer.h

This header file contains the function definitions of the logic to classify the lexemes into different tokens.

## Steps to run the lexer

* Compile the driver.c file by running gcc lexer.c
* Execute a.out and pass the input file name as a command line argument.
* The output of the program is saved as output.txt in the same directory.

## Alpino Language Constructs

* ### Sequential Statements

'var' can be used to declare and define variables in Alpino,without specifying the actual data type like int, float etc.

* ### Conditional Statements

Conditional statements start with an 'if' and other part of condition is written using 'elif'.

* ### Loop Statements

Loops start with the keyword 'loop', followed by paranthesis, an initiator, a condition and a statement.

* ### Functions

Functions can be declared using the keyword 'fun' followed by the name and arguments of the function. The return type and type of arguments need not be specified as Alpino is not strongly typed.

* ### Arrays

Arrays can be declared simply in this way - var arr[] = {}.

## Alpino Token Types

* ### Operator

This includes all the common operators like /, /=, +, +=, -, -=, *, *=, &, &&, |, ||, >, >=, <, <=, :, :=, !, !=

* ### Integer Literals

All valid integers are shown in the integer literal category. They should not begin with a zero, if not equal to zero. The integer should not contain any alphabet and other invalid symbols.

* ### Floating Literals

Floats have a '.' character in the number. The float can start with a dot and multiple zeros in the front as well. The float should also not contain any alphabet and multiple dots also.

* ### Strings

Strings in alpino, can begin with either ', " both and must end with the same character as well. Failure to end the string with the required ' or " will lead to an error. Also, the string should not contain any newline, carriage returns.

* ### Identifiers

These are simply the variable names the user can give. They must start with an alphabet or an underscore and not a digit.

* ### Keywords

These are the reserved keywords by Alpino for its use. For example, loop, var, return etc.

* ### Delimiters

These include all the paranthesis, semi-colons and commas. '[' and ']' are classified as array delimiters.