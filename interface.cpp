#include "interface.h"
#include "board.h"
board* GAME;

const int EASY_GAME_COLUMNS = 15;
const int EASY_GAME_ROWS = 10;
const int EASY_GAME_MINES = EASY_GAME_COLUMNS * EASY_GAME_ROWS * .2;

const int MODERATE_GAME_COLUMNS = 30;
const int MODERATE_GAME_ROWS = 20;
const int MODERATE_GAME_MINES = MODERATE_GAME_COLUMNS * MODERATE_GAME_ROWS * .3;

const int HARD_GAME_COLUMNS = 60;
const int HARD_GAME_ROWS = 40;
const int HARD_GAME_MINES = HARD_GAME_COLUMNS * HARD_GAME_ROWS * .4;

const int EXPERT_GAME_COLUMNS = 120;
const int EXPERT_GAME_ROWS = 80;
const int EXPERT_GAME_MINES = EXPERT_GAME_COLUMNS * EXPERT_GAME_ROWS * .5;

const float MAX_MINE_RATIO = .75;

int buttonPressed(int column, int row, int state)
{
    if (state == LEFT)
        return GAME->begin_play(column, row);
    else if (state == RIGHT)
        return GAME->mark(column, row);
    return ONGOING; //keeps the compiler happy
}

int doubleClick(int column, int row)
{
    return GAME->doubleClick(column, row);
}

int getRows()
{
    return GAME->getRows();
}
int getColumns()
{
    return GAME->getColumns();
}

int newGame(int columns, int rows, int mines)
{
    if (columns < 3)
        return TOO_FEW_COLUMNS_ERROR;
    if (rows < 3)
        return TOO_FEW_ROWS_ERROR;
    if (columns > 200)
        return TOO_MANY_COLUMNS_ERROR;
    if (rows > 200)
        return TOO_MANY_ROWS_ERROR;
    if (mines < 1)
        return TOO_FEW_MINES_ERROR;
    if (mines > (columns * rows * MAX_MINE_RATIO))
        return TOO_MANY_MINES_ERROR;
    GAME = new board(columns, rows, mines);
    return GAME_CREATED; //keeps the compiler happy
}

int newEasyGame()
{
    return newGame(EASY_GAME_COLUMNS, EASY_GAME_ROWS, EASY_GAME_MINES);
}

int newModerateGame()
{
    return newGame(MODERATE_GAME_COLUMNS, MODERATE_GAME_ROWS, MODERATE_GAME_MINES);
}

int newHardGame()
{
    return newGame(HARD_GAME_COLUMNS, HARD_GAME_ROWS, HARD_GAME_MINES);
}

int newExpertGame()
{
    return newGame(EXPERT_GAME_COLUMNS, EXPERT_GAME_ROWS, EXPERT_GAME_MINES);
}

int** getPointer()
{
    return GAME->getArrayPointer();
}
