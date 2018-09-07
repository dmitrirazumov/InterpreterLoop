#include <stdio.h>
#include <stdlib.h>

#include "headers/utilities.h"
#include "headers/loader.h"

int main(int argc, char *argv[]) {

    if (argc != 4) {
        printf("Interpreter LOOP\n\n");
        printf("Wrong format.\nUse: <executable file>.txt <out variables>.txt <result file>.txt\n\n");
        printf("Example code:\n\n");
        printf("i := 2\n");
        printf("LOOP ((10*10+2)-5)/2 DO\n");
        printf("\ti := i + 1\n");
        printf("END\n");
        exit(1);
    }

    char *fileNameProgram = argv[1];
    char *fileNameVariables = argv[2];
    char *fileNameResult = argv[3];

    int fileLenght = countFileChars(fileNameProgram);

    char *memory = (char*) malloc((size_t) (fileLenght + 1));
    if (memory == NULL)
        printError("Unable to allocate the memory.");

    readFile(fileNameProgram, memory);

    struct Program executableProgram;
    executableProgram.startChar = memory;
    executableProgram.currentToken = *((struct Lexem*) malloc(sizeof(struct Lexem)));
    executableProgram.currentToken.name = NULL;
    executableProgram.currentChar = memory;
    executableProgram.fileNameOutVariables = fileNameVariables;
    executableProgram.fileNameResult = fileNameResult;
    executableProgram.variablesCounter = 0;
    executableProgram.variablesPointer = (struct Variable*) malloc(sizeof(struct Variable));

    execute(executableProgram);

    return 0;
}

void readFile(char *fileNameProgram, char *memory) {
    FILE *file;
    if (!(file = fopen(fileNameProgram, "r")))
        printError("Unable to read the program file.");
    char *point = memory;

    do {
        *point = (char) fgetc(file);
        point++;
    } while (!feof(file));
    *(point - 1) = '\0';

    fclose(file);
}

