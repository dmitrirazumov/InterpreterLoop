#include <mem.h>
#include <ctype.h>
#include <stdlib.h>

#include "headers/loader.h"
#include "headers/executor.h"
#include "headers/utilities.h"
#include "headers/tokenReader.h"

#define TOKEN program->currentToken
#define CHAR program->currentChar



int getIdCommand(char *command);

int isWhite(char c) {
    if (c == ' ' || c == '\t') return 1;
    else return 0;
}

int isDelim(char c) {
    if (strchr(" :+-=/%*()", c) || c == '\r' || c == '\n')
        return 1;
    return 0;
}

void readToken(struct Program *program) {
    free(TOKEN.name);
    TOKEN.id = 0;
    TOKEN.type = 0;

    while (isWhite(*CHAR))
        CHAR++;

    if (*CHAR == '\0') {
        TOKEN.id = FINISHED;
        TOKEN.type = DELIMITER;
        return;
    }

    if (*CHAR == '\n') {
        CHAR++;
        TOKEN.id = EOL;
        TOKEN.type = DELIMITER;
        return;
    }

    char *tempStart = CHAR;

    if (strchr(":=+-*/%()<>", *CHAR)) {
        if (*CHAR == ':') {
            CHAR++;
            if (*CHAR == '=') {
                TOKEN.name = mallocAndCopy(tempStart, 2);
                CHAR++;
            } else
                printError("\":=\" expected.");
        } else {
            TOKEN.name = mallocAndCopy(tempStart, 1);
            CHAR++;
        }
        TOKEN.type = DELIMITER;
        return;
    }

    if (isdigit(*CHAR)) {
        int counter = 0;
        while (!isDelim(*CHAR)){
            CHAR++;
            counter++;
        }
        TOKEN.name = mallocAndCopy(tempStart, counter);
        TOKEN.type = NUMBER;
        return;
    }

    if (isalpha(*CHAR)) {
        int counter = 0;
        while (!isDelim(*CHAR)){
            CHAR++;
            counter++;
        }
        TOKEN.name = mallocAndCopy(tempStart, counter);
        TOKEN.id = getIdCommand(TOKEN.name); //а внутреннее представление переменной?
        if (!TOKEN.id)
            TOKEN.type = VARIABLE;
        else
            TOKEN.type = COMMAND;
        return;
    }

    printError("Syntax error! Unknown token.");

}

char * mallocAndCopy(char *source, int steps) {
    char *resultPointer = (char*) malloc(sizeof(char)*(steps + 1));
    char *tempPointer = resultPointer;
    for (int i = 0; i < steps; i++) {
        *tempPointer++ = *source++;
    }
    *tempPointer = '\0';
    return resultPointer;
}

int getIdCommand(char *command) {

    struct Command commands[] = {
            "LOOP", LOOP,
            "DO", DO,
            "END", END,
    };

    for (int i = 0; *commands[i].name; i++) {
        if (!strcmp(commands[i].name, command))
            return commands[i].id;
    }
    return 0;
}