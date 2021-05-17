Virtual ant

ant.h and ant.c
	contains code for the virtual ant, with functions for each of the actions
	
stack.c and stack.h
	implements a stack of nodes which contain an x and y position. Used for the ant's internal memory.

map.h and map.c
	A struct and functions for representing the map and allowing setting and getting the object
	at a given position
	
action.h and action.c
	helper methods for converting an action in string form to an integer, and a function for 
	executing the action on the ant
	
config.h
	contains #define's for constants such as energy and tiles
	
instructionset.h and instructionset.c
	helper struct for holding the intelligence file in memory and reading out actions one by one.