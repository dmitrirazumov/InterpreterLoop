#ifndef INTERPRETERLOOPNEW_EXECUTOR_H
#define INTERPRETERLOOPNEW_EXECUTOR_H

#define MAX_NESTING 30
#define SIZE_LEXEM 100

struct Lexem{
    char *name;
    int id;
    int type;
};

struct Command {
    char name[6];
    int id;
};

struct Loop {
    int source;
    int target;
    char *cycleStart;
};

struct LoopStack {
    struct Loop stack[MAX_NESTING];
    int nestingLevel;
    int maxNesting;
};

struct Variable {
    char *name;
    int value;
};

#endif //INTERPRETERLOOPNEW_EXECUTOR_H
