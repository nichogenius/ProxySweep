#ifndef INTERFACE_H
#define INTERFACE_H

#define LEFT 0
#define RIGHT 1

#define UNVISITED -1
#define UNVISITED_MINE -2
#define FLAG -3
#define QUESTION -4
#define FLAG_MINE -5
#define QUESTION_MINE -6
#define DETONATE -7
#define MINE -8
#define BAD_FLAG -9
#define BAD_QUESTION -10

#define GAME_END_SUCCESS 0
#define GAME_END_FAIL 1
#define ONGOING 2

#define GAME_CREATED 0
#define TOO_FEW_MINES_ERROR 1
#define TOO_FEW_ROWS_ERROR 2
#define TOO_FEW_COLUMNS_ERROR 3
#define TOO_MANY_MINES_ERROR 4
#define TOO_MANY_ROWS_ERROR 5
#define TOO_MANY_COLUMNS_ERROR 6

int buttonPressed(int column, int row, int state);
int doubleClick(int column, int row);
int newGame(int columns, int rows, int mines);
int newEasyGame();
int newModerateGame();
int newHardGame();
int newExpertGame();
int getColumns();
int getRows();
int** getPointer();

#endif // INTERFACE_H
