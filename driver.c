// this c file scans through the input alpino code and seperates appropriate lexemes
// which are then sent to the lexer that return the corresponding token

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

int main(int argc, char* argv[]) {

    char c;
    char* file_name;

    // pointer to a file
    FILE *fptr, *optr;

    // check for valid arguments
    if(argc == 1) {
        printf("Please pass the input file name as an argument\n");
        return 0;
    } else if(argc == 2) {
        optr = fopen("output.txt", "w");
        file_name = argv[1];
    } else {
        printf("Please pass only one file input\n");
        return 0;
    }

    // return error if file cannot be opened
    if((fptr = fopen(file_name, "r")) == NULL) {
        printf("Error opening the file!\n");
        exit(1);
    }

    // peek the next character, without moving the file pointer
    c = peek_next_char(fptr);
    
    // loop through all the characters in the file
    while(c != EOF) {
        
        // move the pointer to the current character, so now we are pointing to the current character
        move_pointer_next(fptr);
        
        if(c == ' ' || c == '\n') {
            //skip
        }
        // checks if the lexeme is an integer literal 
        else if(c >= 48 && c <= 57) {
            lexer_digit_found(c, fptr, ' ', optr);
        }
        // checks if the lexeme is a string literal
        else if(c == '"' || c == '\'') {
            lexer_string_found(c, fptr, optr);
        }
        // checks if the lexeme is a delimiter
        else if(c == '{' || c == '}' || c == '(' || c == ')' || c == ';' || c == ',' || c == '[' || c == ']') {
            if(c != '[' && c!= ']') fprintf(optr, "TK-delimiter, string %c, line number %d\n", c, line_number);
            else fprintf(optr, "TK-array delimiter, string %c, line number %d\n", c, line_number);
        }
        // checks if the lexeme is a keyword or an identifier
        else if((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == '_') {
            lexer_alphabet_found(c, fptr, optr);
        }
        // checks if the lexeme is an operator or a comment
        else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '>' || c == '<' || c == '!' || c == '?' || c == ':' || c == '&' || c == '|') {
            lexer_operator_found(c, fptr, optr);
        }
        // checks if the lexeme is an assignment operator
        else if(c == '=') {
            lexer_assignment_found(c, fptr, optr);
        }

        
        c = peek_next_char(fptr);
    }

    printf("Output saved to output.txt successfully\n");

    // close the file
    fclose(fptr);
    fclose(optr);

    return 0;
}