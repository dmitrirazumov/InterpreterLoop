#include <stdlib.h>

#include "headers/loader.h"
#include "headers/tokenReader.h"
#include "headers/utilities.h"
#include "headers/expressions.h"
#include "headers/loop.h"
#include "headers/variables.h"

void executeToken(struct Program *program);

void endProgram(struct Program *program);

void executeLoop(struct Program *program);

void executeEnd(struct Program *program);

void assignment(struct Program *program);


void execute(struct Program program) {
    struct LoopStack loopStack;
    loopStack.maxNesting = MAX_NESTING;
    loopStack.nestingLevel = 0;

    program.loopStack = loopStack;

    while (program.currentToken.id != FINISHED) {
        readToken(&program);
        executeToken(&program);
    }

    endProgram(&program);

}

void endProgram(struct Program *program) {

    if (program->loopStack.nestingLevel != 0) {
        printError("Loop is not closed with \"END\"");
    }

    writeResult(program->fileNameOutVariables, program);

    free(program->currentToken.name);
    free(program->loopStack.stack);
    free(program->startChar);
}

void executeToken(struct Program *program) {
    if (program->currentToken.id == FINISHED) {
        endProgram(program);
    }

    if (program->currentToken.type == VARIABLE) {
        assignment(program);
    }

    if (program->currentToken.type == COMMAND) {
        switch (program->currentToken.id) {
            case LOOP:
                executeLoop(program);
                break;
            case END:
                executeEnd(program);
            default:
                break;
        }
    }
}

void assignment(struct Program *program) {
    int value;
    struct Variable *var;
    if ((var = findVariable(program->currentToken.name, program)) == NULL)
        printError("Incorrect variable");
    readToken(program);
    calcExpression(&value, program);
    var->value = value;
}

void executeEnd(struct Program *program) {
    struct Loop loop;

    loop = loopPop(program);

    loop.source++;
    if (loop.source > loop.target)
        return;
    loopPush(loop, program);
    program->currentChar = loop.cycleStart;
}

void executeLoop(struct Program *program) {
    struct Loop currentLoop;

    currentLoop.source = 1;

    int loop_iterations = 0;

    calcExpression(&loop_iterations, program);

    currentLoop.target = loop_iterations;

    if (currentLoop.target < currentLoop.source) {
        int counter = 0;

        do {

            switch (program->currentToken.id) {
                case FINISHED:
                    printError("Syntax error.");
                    break;
                case LOOP:
                    counter++;
                    break;
                case END:
                    counter--;
                    break;
                default:
                    break;
            }
            readToken(program);

        } while (program->currentToken.id != END || counter != 0);

        return;
    }

    if (program->currentToken.id != DO)
        printError("Expected \"DO\" in LOOP construction");
    currentLoop.cycleStart = program->currentChar;
    loopPush(currentLoop, program);
}


