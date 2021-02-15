// this c file scans through the input alpino code and seperates appropriate lexemes
// which are then sent to the lexer that return the corresponding token
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEYWORDS_SIZE 10

int line_number = 1;

// store the reserved keywords of the language in an array
char* keywords[] = {"fun", "var", "return", "if", "elif", "break", "continue", "loop", "from", "to"};

// returns the next character without moving the file pointer
char peek_next_char(FILE* fptr) {
    char c = fgetc(fptr);
    fseek(fptr, -1, SEEK_CUR);

    return c;
}

// increments the file pointer by one to the right, also takes care of line number
void move_pointer_next(FILE* fptr) {
    char c = fgetc(fptr);
    if(c == '\n') line_number++;
}

// decrements the file pointer by one to the left
void move_pointer_back(FILE* fptr) {
    fseek(fptr, -1, SEEK_CUR);
}

// moves the pointer to the last white space or to the last valid character
void skip_white_spaces(FILE* fptr) {
    char c_next = peek_next_char(fptr);
    if(c_next != ' ' && c_next != '\n') return;
    while(c_next == ' ' || c_next == '\n') {
        if(c_next == '\n') line_number++;
        move_pointer_next(fptr);
        c_next = peek_next_char(fptr);
    }
}


// after all the methods, the file pointer should point to the last valid character of the lexeme found

void lexer_assignment_found(char c, FILE* fptr) {
    char c_next = peek_next_char(fptr);
    if(c_next == '=') {
        printf("TK-operator, string ==, line number %d\n", line_number);
        move_pointer_next(fptr);
    }
    else printf("TK-assignment, string =, line number %d\n", line_number);

    skip_white_spaces(fptr);

    c_next = peek_next_char(fptr);

    // checks if the next character is an identifier
    if((c_next >= 65 && c_next <= 90) || (c_next >= 97 && c_next <= 122) || c_next == '_') {
        return;
    } else if (c_next == '+' || c_next == '-' || (c_next >= 48 && c_next <= 57)) {
        // the lexeme is an integer literal
        char str[] = "";

        if(c_next == '+' || c_next == '-') {
            strncat(str, &c_next, 1);
            move_pointer_next(fptr);
            skip_white_spaces(fptr);
        }

        c_next = peek_next_char(fptr);

        while(c_next >= 48 && c_next <= 57) {
            strncat(str, &c_next, 1);
            move_pointer_next(fptr);
            c_next = peek_next_char(fptr);
        }

        char* s_copy;
        s_copy = (char*)malloc(100*sizeof(char));
        strcpy(s_copy, str);

        char str2[100] = "TK-integer, string ";
        strcat(str2, s_copy);

        char* s;
        s = (char*)malloc(200*sizeof(char));
        strcpy(s, str2);

        printf("%s, line number %d\n", s, line_number);
        return;

    } else {
        //error in finding token
    }
}

void lexer_alphabet_found(char c, FILE* fptr) {
    // the lexeme can either be a keyword or an identifier
    
    // s_temp is the word character array which will store the lexeme
    char s_temp[] = "";
    char c_next = c;

    // move the pointer forward till we see an alphabet, a digit or and underscore
    while((c_next >= 65 && c_next <= 90) || (c_next >= 97 && c_next <= 122) || (c_next >= 48 && c_next <= 57) || c_next == '_') {
        strncat(s_temp, &c_next, 1);
        c_next = peek_next_char(fptr);
        move_pointer_next(fptr);
    }
    move_pointer_back(fptr);

    // save a copy of s_temp array as a char pointer
    char* s_copy;
    s_copy = (char*)malloc(100*sizeof(char));
    strcpy(s_copy, s_temp);

    // search for the word in the keywords array
    for(int i = 0;i < KEYWORDS_SIZE; i++) {
        if(strcmp(keywords[i], s_temp) == 0) {
            char str[100] = "TK-keyword, string ";
            strcat(str, keywords[i]);

            char* s;
            s = (char*)malloc(100*sizeof(char));
            strcpy(s, str);

            printf("%s, line number %d\n", s, line_number);
            return;
        }
    }

    // if the lexeme is not a keyword
    char str[100] = "TK-identifier, string ";
    strcat(str, s_copy);

    char* s;
    s = (char*)malloc(200*sizeof(char));
    strcpy(s, str);

    printf("%s, line number %d\n", s, line_number);
    return;
}

void lexer_operator_found(char c, FILE* fptr) {
    // here we check for these possibilities - whether the lexeme is an operator or a comment or an integer
    char c_next = peek_next_char(fptr);

    switch(c) {

        case '/':
            if(c_next == '/') {
                move_pointer_next(fptr);
                c_next = peek_next_char(fptr);
                // to ignore the comment statement, move the file pointer forward till the next line or the end of file
                while(c_next != '\n' && c_next != EOF) {
                    move_pointer_next(fptr);
                    c_next = peek_next_char(fptr);
                }
                printf("TK-comment, string //, line number %d\n", line_number);
                return;
            } else return;

        case '+':
            if(c_next == '+') {
                move_pointer_next(fptr);
                printf("TK-operator, string ++, line number %d\n", line_number);
            } else {
                printf("TK-operator, string +, line number %d\n", line_number);
                skip_white_spaces(fptr);

                // we have an integer literal in arithmetic operation
                c_next = peek_next_char(fptr);
                if(c_next >= 48 && c_next <= 57) {
                    char str[] = "";
                    
                    while(c_next >= 48 && c_next <= 57) {
                        strncat(str, &c_next, 1);
                        move_pointer_next(fptr);
                        c_next = peek_next_char(fptr);
                    }

                    printf("TK-integer, string %s, line number %d\n", str, line_number);
                }
            }
            return;

        case '-':
            if(c_next == '-') {
                move_pointer_next(fptr);
                printf("TK-operator, string --, line number %d\n", line_number);
            } else {
                printf("TK-operator, string -, line number %d\n", line_number);
                skip_white_spaces(fptr);

                // we have an integer literal in arithmetic operation
                c_next = peek_next_char(fptr);
                if(c_next >= 48 && c_next <= 57) {
                    char str[] = "";
                    
                    while(c_next >= 48 && c_next <= 57) {
                        strncat(str, &c_next, 1);
                        move_pointer_next(fptr);
                        c_next = peek_next_char(fptr);
                    }

                    printf("TK-integer, string %s, line number %d\n", str, line_number);
                }
            }
            return;

        case ':':
            if(c_next == '=') {
                move_pointer_next(fptr);
                printf("TK-operator, string :=, line number %d\n", line_number);
            } else {
                printf("TK-operator, string :, line number %d\n", line_number);
            }
            return;
        
        case '>':
            if(c_next == '=') {
                move_pointer_next(fptr);
                printf("TK-operator, string >=, line number %d\n", line_number);
            } else {
                printf("TK-operator, string >, line number %d\n", line_number);
            }
            return;

        case '<':
            if(c_next == '=') {
                move_pointer_next(fptr);
                printf("TK-operator, string <=, line number %d\n", line_number);
            } else {
                printf("TK-operator, string <, line number %d\n", line_number);
            }
            return;

        case '!':
            if(c_next == '=') {
                move_pointer_next(fptr);
                printf("TK-operator, string !=, line number %d\n", line_number);
            } else {
                printf("TK-operator, string !, line number %d\n", line_number);
            }
            return;

        case '&':
            if(c_next == '&') {
                move_pointer_next(fptr);
                printf("TK-operator, string &&, line number %d\n", line_number);
            } else {
                printf("TK-operator, string &, line number %d\n", line_number);
            }
            return;

        case '|':
            if(c_next == '|') {
                move_pointer_next(fptr);
                printf("TK-operator, string ||, line number %d\n", line_number);
            } else {
                printf("TK-operator, string |, line number %d\n", line_number);
            }
            return;

        default:
            break;
    }

    return;
}

int main() {
    // pointer to a file
    char c;
    FILE* fptr;

    // return error if file cannot be opened
    if((fptr = fopen("./input.al", "r")) == NULL) {
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
            
        }
        // checks if the lexeme is a keyword or an identifier
        else if((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == '_') {
            lexer_alphabet_found(c, fptr);
        }
        // checks if the lexeme is an operator or a comment
        else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '>' || c == '<' || c == '!' || c == '?' || c == ':' || c == '&' || c == '|') {
            lexer_operator_found(c, fptr);
        }
        // checks if the lexeme is an assignment operator
        else if(c == '=') {
            lexer_assignment_found(c, fptr);
        }

        
        c = peek_next_char(fptr);
    }

    // close the file
    fclose(fptr);

    return 0;
}