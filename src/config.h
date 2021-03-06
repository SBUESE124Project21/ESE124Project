#pragma once

#define DIR_RIGHT 0
#define DIR_UP 1
#define DIR_LEFT 2 
#define DIR_DOWN 3

#define TILE_SPACE ' '
#define TILE_WALL '*'
#define TILE_GOLD '@'
#define TILE_PHEROMONE 'p'
#define TILE_OUTSIDE '_'

#define MAX_INSTRUCTIONSIZE 512
#define MAX_STACKSIZE 100
#define MAX_BUFFERSIZE 1024

#define MAX_ENERGY 10000

#define MARK_ENERGY 3
#define MOVE_ENERGY 3
#define CHECK_ENERGY 1
#define PUSH_POP_ENERGY 4
#define PEEK_CLEAR_ENERGY 2
#define BJPI_ENERGY 5
#define CJPI_ENERGY 3

#define C_MARK 0
#define C_MOVE_F 1
#define C_MOVE_B 2
#define C_MOVE_L 3
#define C_MOVE_R 4
#define C_CWF 5
#define C_CWB 6
#define C_CWL 7
#define C_CWR 8
#define C_PUSH 9
#define C_POP 10
#define C_PEEK 11
#define C_CLEAR 12
#define C_BJPI 13
#define C_CJPI 14
#define C_BACKTRACK 15
#define C_RP 16
