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
	node startPosition = getStartPosition(map);
	if(startPosition.x < 0 || startPosition.y < 0){
		printf("Failed to find open space in wall as start position.");
		exit(1);
	}
	ant* a = makeAnt(startPosition.x, startPosition.y, MAX_ENERGY);
	printMap(map, outputFile);
	//close files no longer necessary
	fclose(mapFile);
	fclose(intelligenceFile);
	
	char* instruction = (char*)calloc(MAX_BUFFERSIZE, sizeof(char));	//string to hold instruction
	while((instr->position < instr->count) && isAlive(a)){	//until the end of the instruction set
		getNextInstruction(instr, instruction);	//read the next instruction into instruction string
		
		int action = convertAction(instruction); //convert the string to an int
		if(action == -1){
			fprintf(outputFile, "Error: Illegal action number %d: '%s'.", instr->position, instruction);
			exit(1);
		}
		else if(action == C_RP){						// if its RP n t, then deal with it separately
			int j,k;
			char s[10];
			int n;
			int t;
			int cpos = instr->position;
			int epos;
			sscanf(instruction, "%s %d %d", s, &n, &t);	// read the n and t values from the instruction
			for(k = 0; k < t && isAlive(a); k++){						// t times
				for(j = 0; j < n && isAlive(a); j++){					//execute the next n instructions
					
					getNextInstruction(instr, instruction);	//get the instruction
					action = convertAction(instruction);	//convert it
					if(action == -1){
						fprintf(outputFile, "Error: Illegal action number %d: '%s'.", instr->position, instruction);
						exit(1);
					}
					executeAction(map, a, action);			//execute the action
					fprintf(outputFile, "Executed action '%s'. Position: (%d, %d). Remaining energy: %d. Collected gold: %d\n", instruction ,a->currentPosition.x, a->currentPosition.y, a->energy, a->collectedGold);
				}
				epos = instr->position;					//save the end position so if this is the last loop, we dont end up repeating things one too many times.
				instr->position = cpos;					//reset the position back to just after the RP to repeat again
			}
			instr->position = epos;
		}
		else{
			executeAction(map, a, action);				//execute the action if its not rp
			fprintf(outputFile, "Executed action '%s'. Position: (%d, %d). Remaining energy: %d. Collected gold: %d\n", instruction, a->currentPosition.x, a->currentPosition.y, a->energy, a->collectedGold);
		}
		
	}
	
	free(instruction);
	freeInstructionset(instr);
	freeMap(map);
	fclose(outputFile);
	return 0;
}
