//this c file scans through the input alpino code and seperates appropriate lexemes
//which are then sent to the lexer that return the corresponding token

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//store the reserved keywords of the language in an array
char* keywords[] = {"fun", "var", "return", "if", "elif", "break", "continue", "loop", "from", "to"};

char peek_next_char(FILE* fptr) {
    char c = fgetc(fptr);
    fseek(fptr, -1, SEEK_CUR);

    return c;
}

void move_pointer_next(FILE* fptr) {
    fseek(fptr, 1, SEEK_CUR);
}

char* lexer_operator_found(char c, FILE* fptr) {
    char c_next = peek_next_char(fptr);

    switch(c) {

        case '/':
            if(c_next == '/') {
                move_pointer_next(fptr);
                while(c_next != '\n') {
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

    char s_temp[] = "TK-operator, string ";
    strncat(s_temp, &c, 1);
    char* s;
    s = (char*)malloc(50*sizeof(char));
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

        //printf("%c", c);
        if(c == '\n') line_number++;
        move_pointer_next(fptr);
        
        if(c == ' ' || c == '\n') {
            
        }
        else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '>' || c == '<' || c == '!' || c == '?' || c == ':' || c == '&' || c == '|') {
            char* str = lexer_operator_found(c, fptr);
            printf("%s, line number %d\n", str, line_number);
        }

        
        c = peek_next_char(fptr);
    }

    fclose(fptr);

    return 0;
}