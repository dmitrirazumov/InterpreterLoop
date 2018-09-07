#ifndef INTERPRETERLOOPNEW_TOKENREADER_H
#define INTERPRETERLOOPNEW_TOKENREADER_H

#define DELIMITER  1
#define VARIABLE   2
#define NUMBER     3
#define COMMAND    4

#define LOOP 10
#define DO 11
#define END 15
#define EOL 16
#define FINISHED 17

int isWhite(char ch);
int isDelim(char ch);
void readToken(struct Program *program);
char *mallocAndCopy(char *start, int name);

#endif //INTERPRETERLOOPNEW_TOKENREADER_H
