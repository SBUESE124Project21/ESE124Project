#include <stdio.h>
#include <stdlib.h>
#include "ant.h"
#include "config.h"
#include "instructionset.h"
#include "action.h"

#define MAPFILENAME "mapfile.txt"
#define INTELLIGENCEFILENAME "intelligencefile.txt"
#define OUTPUTFILENAME "outputfile.txt"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	FILE* mapFile;
	FILE* intelligenceFile;
	FILE* outputFile;
	
	/*Load map, intelligence, and output files*/
	if((mapFile = fopen(MAPFILENAME, "r")) == NULL){
		printf("Failed to open map file, '%s'", MAPFILENAME);
		exit(1);
	}	
	if((intelligenceFile = fopen(INTELLIGENCEFILENAME, "r")) == NULL){
		printf("Failed to open intelligence file, '%s'", INTELLIGENCEFILENAME);
		exit(1);
	}	
	if((outputFile = fopen(OUTPUTFILENAME, "w")) == NULL){
		printf("Failed to open output file, '%s'", OUTPUTFILENAME);
		exit(1);
	}
	
	//Load map and instructions
	map* map = loadMap(mapFile);
	instructionset* instr = loadInstructionSet(intelligenceFile, 512);
	node startPosition = getStartPosition(m);
	ant* a = makeAnt(startPosition->x, startPosition->y, MAX_ENERGY);
	
	//close files no longer necessary
	fclose(mapFile);
	fclose(intelligenceFile);
	
	char* instruction = (char*)calloc(MAX_BUFFERSIZE, sizeof(char));	//string to hold instruction
	while(instr->position < instr->count && ){	//until the end of the instruction set
		getNextInstruction(instr, instruction);	//read the next instruction into instruction string
		
		int action = convertAction(instruction);
		
		if(action == C_RP){
			
		}
		else{
			execute
		}
		
	}
	
	free(instruction);
	freeInstructionset(instr);
	freeMap(map);
	fclose(outputFile);
	return 0;
}
