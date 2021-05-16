#pragma once
#include <stdio.h>

typedef struct instructionset instructionset;

struct instructionset{
	char** instructions;
	int position;
	int count;
	int maxCount;
};

instructionset* makeInstructionset(int maxCount);
instructionset* loadInstructionSet(FILE* instructionFile, int max);
void freeInstructionset(instructionset* i);
void addInstruction(instructionset* i, char* instruction);
char* getNextInstruction(instructionset* i, char* buf);
void rewindInstructionset(instructionset* i, int d);


