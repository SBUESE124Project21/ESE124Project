#include "config.h"
#include "ant.h"
#include "map.h"

int convertAction(char* actionstr);
char* stringToUpper(char* str);
int executeAction(map* m, ant* a, int action);
