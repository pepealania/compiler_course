#include <stdio.h>
#include <ctype.h>

const char *src = "x = x * 1";

typedef enum {
    TOK_IDENTIFIER,
    TOK_ASSIGN,
    TOK_PLUS,
    TOK_MULT,
    TOK_NUMBER,
    TOK_EOF
} TokenType;

typedef struct {
    TokenType type;
    char text[64];
} Token;

Token token;

void next_token() {

    /* skip whitespace */
    while (isspace(*src))
        src++;

    /* end of input */
    if (*src == '\0') {
        token.type = TOK_EOF;
        return;
    }

    /* identifier */
    if (isalpha(*src)) {

        int i = 0;

        while (isalnum(*src)) {
            token.text[i++] = *src++;
        }

        token.text[i] = '\0';

        token.type = TOK_IDENTIFIER;
        return;
    }

    /* number */
    if (isdigit(*src)) {

        int i = 0;

        while (isdigit(*src)) {
            token.text[i++] = *src++;
        }

        token.text[i] = '\0';

        token.type = TOK_NUMBER;
        return;
    }

    /* operators */
    switch (*src) {

        case '=':
            token.type = TOK_ASSIGN;
            token.text[0] = '=';
            token.text[1] = '\0';
            src++;
            return;

        case '+':
            token.type = TOK_PLUS;
            token.text[0] = '+';
            token.text[1] = '\0';
            src++;
            return;
        case '*':
            token.type = TOK_MULT;
            token.text[0] = '*';
            token.text[1] = '\0';
            src++;
            return;            
    }

    printf("Unknown character: %c\n", *src);
    src++;
}

const char *token_name(TokenType t) {

    switch (t) {
        case TOK_IDENTIFIER: return "IDENTIFIER";
        case TOK_ASSIGN: return "ASSIGN";
        case TOK_PLUS: return "PLUS";
        case TOK_MULT: return "MULT";
        case TOK_NUMBER: return "NUMBER";
        case TOK_EOF: return "EOF";
    }

    return "UNKNOWN";
}

int main() {

    do {
        next_token();

        printf("%s : %s\n",
               token_name(token.type),
               token.text);

    } while (token.type != TOK_EOF);

    return 0;
}
