#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100

// Define token types
typedef enum {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_DELIMITER,
    TOKEN_UNKNOWN
} TokenType;

// List of keywords
const char *keywords[] = {"if", "else", "while", "return", "int", "float", "void"};
const int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

// Check if a word is a keyword
int isKeyword(const char *word) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Print token
void printToken(TokenType type, const char *value) {
    const char *type_str[] = {
        "Keyword", "Identifier", "Number", "Operator", "Delimiter", "Unknown"
    };
    printf("%s: %s\n", type_str[type], value);
}

// Lexical analyzer function
void lexicalAnalyzer(const char *source) {
    int i = 0;
    char token[MAX_TOKEN_LENGTH];
    int tokenIndex = 0;

    enum { START, IN_IDENTIFIER, IN_NUMBER, IN_OPERATOR, IN_DELIMITER } state = START;

    while (source[i] != '\0') {
        char current = source[i];

        switch (state) {
            case START:
                if (isalpha(current)) {
                    state = IN_IDENTIFIER;
                    token[tokenIndex++] = current;
                } else if (isdigit(current)) {
                    state = IN_NUMBER;
                    token[tokenIndex++] = current;
                } else if (strchr("+-*/=", current)) {
                    state = IN_OPERATOR;
                    token[tokenIndex++] = current;
                } else if (strchr(";,(){}", current)) {
                    state = IN_DELIMITER;
                    token[tokenIndex++] = current;
                } else if (isspace(current)) {
                    // Ignore whitespace
                } else {
                    token[tokenIndex++] = current;
                    printToken(TOKEN_UNKNOWN, token);
                    tokenIndex = 0;
                }
                break;

            case IN_IDENTIFIER:
                if (isalnum(current)) {
                    token[tokenIndex++] = current;
                } else {
                    token[tokenIndex] = '\0';
                    state = START;
                    if (isKeyword(token)) {
                        printToken(TOKEN_KEYWORD, token);
                    } else {
                        printToken(TOKEN_IDENTIFIER, token);
                    }
                    tokenIndex = 0;
                    continue; // Reprocess current character
                }
                break;

            case IN_NUMBER:
                if (isdigit(current)) {
                    token[tokenIndex++] = current;
                } else {
                    token[tokenIndex] = '\0';
                    printToken(TOKEN_NUMBER, token);
                    state = START;
                    tokenIndex = 0;
                    continue; // Reprocess current character
                }
                break;

            case IN_OPERATOR:
                token[tokenIndex] = '\0';
                printToken(TOKEN_OPERATOR, token);
                state = START;
                tokenIndex = 0;
                continue; // Reprocess current character
                break;

            case IN_DELIMITER:
                token[tokenIndex] = '\0';
                printToken(TOKEN_DELIMITER, token);
                state = START;
                tokenIndex = 0;
                continue; // Reprocess current character
                break;
        }
        i++;
    }

    // Final token processing (if any)
    if (tokenIndex > 0) {
        token[tokenIndex] = '\0';
        switch (state) {
            case IN_IDENTIFIER:
                if (isKeyword(token)) {
                    printToken(TOKEN_KEYWORD, token);
                } else {
                    printToken(TOKEN_IDENTIFIER, token);
                }
                break;
            case IN_NUMBER:
                printToken(TOKEN_NUMBER, token);
                break;
            case IN_OPERATOR:
                printToken(TOKEN_OPERATOR, token);
                break;
            case IN_DELIMITER:
                printToken(TOKEN_DELIMITER, token);
                break;
            default:
                printToken(TOKEN_UNKNOWN, token);
                break;
        }
    }
}

int main() {
    const char *source_code = "int main() { int a = 10; if (a > 5) return a; }";

    printf("Tokenizing the source code:\n");
    lexicalAnalyzer(source_code);

    return 0;
}
