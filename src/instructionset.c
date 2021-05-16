#include "instructionset.h"

instructionset* makeInstructionset(int maxCount){
	(instructionset*) ins = (instructionset*)calloc(1, sizeof(instructionset));
	ins->instructions = (char**)calloc(maxCount, sizeof(char*));
	ins->count = 0;
	ins->maxCount = maxCount;
	ins->position = 0;
	return ins;
}

instructionset* loadInstructionSet(FILE* instructionFile, int max){
	instructionset* ins = makeInstructionset(max);
	char* buf = (char*)calloc(MAX_BUFFERSIZE, sizeof(char));
	while(ins->count < ins->maxCount && fgets(buf, MAX_BUFFERSIZE, mapfile) != NULL){
		addInstruction(ins, buf);
	}
	return ins;
}

void freeInstructionset(instructionset* instr){
	int i = 0;
	for(i = 0; i < instr->count; i++){
		free(instr->instructions[i]);
	}
	free(instr->instructions);
	free(instr);
}

void addInstruction(instructionset* i, char* instruction){
	if(i->count < i->maxCount){
		char* newins = (char*)calloc(strlen(instruction)+1, sizeof(char));
		strcpy(newins, instruction);
		i->instructions[i->count] = newins;
		i->count++;
	}
}
char* getNextInstruction(instructionset* i, char* buf){
	strcpy(buf, i->instructions[i->position]);
	i->position++;
}
void rewindInstructionset(instructionset* i, int d){
	i->position -= d;
}

