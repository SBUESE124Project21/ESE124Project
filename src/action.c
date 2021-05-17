#include "action.h"
#include <string.h>
#include <stdlib.h>

char* stringToUpper(char* str){
	int i = 0;
	for(i = 0; i < strlen(str); i++){
		str[i] = toupper(str[i]);
	}
	return str;
}

int convertAction(char* actionstr){
	char* actions[] = {
		"MARK",
		"MOVE_F",
		"MOVE_B",
		"MOVE_L",
		"MOVE_R",
		"CWF",
		"CWB",
		"CWL",
		"CWR",
		"PUSH",
		"POP",
		"PEEK",
		"CLEAR",
		"BJPI",
		"CJPI",
		"BACKTRACK",
		"RP"
	};
	char* buf = (char*)calloc(strlen(actionstr)+1, sizeof(char));
	strcpy(buf, actionstr);
	char* act = strtok(buf, " ");
	
	int i = 0;
	for(i = 0; i < 17; i++){
		if(strcmp(actions[i], stringToUpper(act)) == 0){
			free(buf);
			return i;
		}
	}
	free(buf);
	return -1;
}

int executeAction(map* m, ant* a, int action){
	switch(action){
		case C_MARK:
			mark(m, a);
			break;
		case C_MOVE_F:
			move_f(m,a);
			break;
		case C_MOVE_B:
			move_b(m,a);
			break;
		case C_MOVE_L:
			move_l(m,a);
			break;
		case C_MOVE_R:
			move_r(m,a);
			break;
		case C_CWF:
			cwf(m,a);
			break;
		case C_CWB:
			cwb(m,a);
			break;
		case C_CWL:
			cwl(m,a);
			break;
		case C_CWR:
			cwr(m,a);
			break;
		case C_PUSH:
			push(a);
			break;
		case C_POP:
			pop(a);
			break;
		case C_PEEK:
			peek(a);
			break;
		case C_CLEAR:
			clear(a);
			break;
		case C_BJPI:
			bjpi(m,a);
			break;
		case C_CJPI:
			cjpi(m,a);
			break;
		case C_BACKTRACK:
			backtrack(a);
			break;
		default:
			return 0;
			break;
	}
	return 1;
}

