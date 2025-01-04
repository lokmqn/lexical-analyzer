#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100

// Token types
typedef enum {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_DELIMITER,
    TOKEN_UNKNOWN
} TokenType;

//keywords
const char *keywords[] = {"if", "else", "while", "return", "int", "float", "void"};
const int num_keywords = sizeof(keywords) / sizeof(keywords[0]);


int isKeyword(const char *word) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


void printToken(TokenType type, const char *value) {
    const char *type_str[] = {
        "Keyword", "Identifier", "Number", "Operator", "Delimiter", "Unknown"
    };
    printf("%s: %s\n", type_str[type], value);
}


void analyzeToken(const char *input) {
    char token[MAX_TOKEN_LENGTH];
    int i = 0;
    int length = strlen(input);

    while (i < length) {
        char current = input[i];

        if (isalpha(current)) {
            int j = 0;
            while (i < length && (isalnum(input[i]) || input[i] == '_')) {
                token[j++] = input[i++];
            }
            token[j] = '\0';
            if (isKeyword(token)) {
                printToken(TOKEN_KEYWORD, token);
            } else {
                printToken(TOKEN_IDENTIFIER, token);
            }
        }

        else if (isdigit(current)) {
            int j = 0;
            while (i < length && isdigit(input[i])) {
                token[j++] = input[i++];
            }
            token[j] = '\0';
            printToken(TOKEN_NUMBER, token);
        }

        else if (strchr("+-*/=><", current)) {
            token[0] = current;
            token[1] = '\0';
            printToken(TOKEN_OPERATOR, token);
            i++;
        }

        else if (strchr(";,(){}[]", current)) {
            token[0] = current;
            token[1] = '\0';
            printToken(TOKEN_DELIMITER, token);
            i++;
        }

        else if (isspace(current)) {
            i++;
        }

        else {
            token[0] = current;
            token[1] = '\0';
            printToken(TOKEN_UNKNOWN, token);
            i++;
        }
    }
}

int main() {
    char input[MAX_TOKEN_LENGTH];

    printf("Lexical Analyzer - Type input and get token types (type 'exit' to quit):\n");

    while (1) {
        printf("\nEnter input: ");
        fgets(input, MAX_TOKEN_LENGTH, stdin);


        input[strcspn(input, "\n")] = '\0';


        if (strcmp(input, "exit") == 0) {
            printf("Exiting the program.\n");
            break;
        }


        analyzeToken(input);
    }

    return 0;
}
