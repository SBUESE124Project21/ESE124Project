#include "action.h"

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
	
	char* act = strtok(actionstr, " ");
	
	int i = 0;
	for(i = 0; i < 17; i++){
		if(strcmp(actions[i], stringToUpper(act)) == 0){
			return i;
		}
	}
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
			break
		case C_MOVE_L:
			move_l(m,a);
			break;
		case C_MOVE_R:
			move_r(m,a);
			break
		case C_CWF:
			cwf(m,a);
			break;
		case C_CWB:
			cwb(m,a);
			break;
		case C_CWl:
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
			bjpi(a);
			break;
		case C_CJPI:
			cjpi(a);
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

