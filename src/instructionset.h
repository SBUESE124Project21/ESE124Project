#pragma once
typedef struct instructionset instructionset;

struct instructionset{
	char** instructions;
	int position;
	int count;
	int maxCount;
};

instructionset* createInstructionset(int maxCount);
void freeInstructionset(instructionset* i);
void addInstruction(char* instruction);
char* getNextInstruction(instructionset* i, char* buf);
void rewindInstructionset(instructionset* i, int d);


