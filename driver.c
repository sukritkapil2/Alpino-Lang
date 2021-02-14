//this c file scans through the input alpino code and seperates appropriate lexemes
//which are then sent to the lexer that return the corresponding token
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEYWORDS_SIZE 10

//store the reserved keywords of the language in an array
char* keywords[] = {"fun", "var", "return", "if", "elif", "break", "continue", "loop", "from", "to"};

// returns the next character without moving the file pointer
char peek_next_char(FILE* fptr) {
    char c = fgetc(fptr);
    fseek(fptr, -1, SEEK_CUR);

    return c;
}

// increments the file pointer by one to the right
void move_pointer_next(FILE* fptr) {
    fseek(fptr, 1, SEEK_CUR);
}

// decrements the file pointer by one to the left
void move_pointer_back(FILE* fptr) {
    fseek(fptr, -1, SEEK_CUR);
}

char* lexer_alphabet_found(char c, FILE* fptr) {
    // the lexeme can either be a keyword or an identifier
    
    //s_temp is the word character array
    char s_temp[] = "";
    char c_next = c;
    int size = 0;

    while((c_next >= 65 && c_next <= 90) || (c_next >= 97 && c_next <= 122) || (c_next >= 48 && c_next <= 57) || c_next == '_') {
        strncat(s_temp, &c_next, 1);
        //printf("%c\n", c_next);
        c_next = peek_next_char(fptr);
        move_pointer_next(fptr);
        size++;
    }
    move_pointer_back(fptr);

    // save a copy of s_temp array as a char pointer
    char* s_copy;
    s_copy = (char*)malloc(100*sizeof(char));
    strcpy(s_copy, s_temp);

    //search for the word in the keywords array
    for(int i = 0;i < KEYWORDS_SIZE; i++) {
        if(strcmp(keywords[i], s_temp) == 0) {
            char str[100] = "TK-keyword, string ";
            strcat(str, keywords[i]);

            char* s;
            s = (char*)malloc(100*sizeof(char));
            strcpy(s, str);

            return s;
        }
    }

    char str[100] = "TK-identifier, string ";
    strcat(str, s_copy);

    char* s;
    s = (char*)malloc(200*sizeof(char));
    strcpy(s, str);

    return s;
}

char* lexer_operator_found(char c, FILE* fptr) {
    // here we check for two possibilities - whether the lexeme is an operator or a comment
    char c_next = peek_next_char(fptr);

    switch(c) {

        case '/':
            if(c_next == '/') {
                move_pointer_next(fptr);
                //to ignore the comment statement, move the file pointer forward till the next line or the end of file
                while(c_next != '\n' && c_next != EOF) {
                    move_pointer_next(fptr);
                    c_next = peek_next_char(fptr);
                }
                return "TK-comment, string //";
            } else break;

        case '+':
            if(c_next == '+') {
                move_pointer_next(fptr);
                return "TK-operator, string ++";
            } else break;

        case ':':
            if(c_next == '=') {
                move_pointer_next(fptr);
                return "TK-operator, string :=";
            } else break;
        
        case '>':
            if(c_next == '=') {
                move_pointer_next(fptr);
                return "TK-operator, string >=";
            } else break;

        case '<':
            if(c_next == '=') {
                move_pointer_next(fptr);
                return "TK-operator, string <=";
            } else break;

        case '!':
            if(c_next == '=') {
                move_pointer_next(fptr);
                return "TK-operator, string !=";
            } else break;

        case '&':
            if(c_next == '&') {
                move_pointer_next(fptr);
                return "TK-operator, string &&";
            } else break;

        case '|':
            if(c_next == '|') {
                move_pointer_next(fptr);
                return "TK-operator, string ||";
            } else break;

        default:
            break;
    }

    char s_temp[24] = "TK-operator, string ";
    strncat(s_temp, &c, 1);
    char* s;
    s = (char*)malloc(24*sizeof(char));
    strcpy(s, s_temp);

    return s;
}

int main() {
    //pointer to a file
    char c;
    FILE* fptr;
    int line_number = 1;

    if((fptr = fopen("./input.al", "r")) == NULL) {
        printf("Error opening the file!\n");
        exit(1);
    }

    //c is the character in the file
    c = peek_next_char(fptr);
    
    //loop through all the characters in the file
    while(c != EOF) {
        //printf("%c\n", c);
        //printf("%c", c);
        if(c == '\n') line_number++;
        move_pointer_next(fptr);
        
        if(c == ' ' || c == '\n') {
            
        }
        //checks if the lexeme is a keyword or an identifier
        else if((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) {
            char* str = lexer_alphabet_found(c, fptr);
            printf("%s, line number %d\n", str, line_number);
        }
        //checks if the lexeme is an operator or a comment
        else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '>' || c == '<' || c == '!' || c == '?' || c == ':' || c == '&' || c == '|') {
            char* str = lexer_operator_found(c, fptr);
            printf("%s, line number %d\n", str, line_number);
        }

        
        c = peek_next_char(fptr);
    }

    fclose(fptr);

    return 0;
}