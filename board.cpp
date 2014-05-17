#include "board.h"
#include "interface.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

board::board(int columns_in, int rows_in, int mines_in)
{
    first_click = true;
    columns = columns_in;
    rows = rows_in;
    mines = mines_in;
    flags = 0;
    game_board = new int*[columns];
    for (int i = 0; i < columns; ++i)
    {
        game_board[i] = new int[rows];
        for (int j = 0; j < rows; ++j)
            setState(i, j, UNVISITED);
    }
}

bool board::inBounds(int column, int row)
{
    if (column < 0)
        return false;
    if (column >= columns)
        return false;
    if (row < 0)
        return false;
    if (row >= rows)
        return false;
    return true;
}

bool board::inMines(int column, int row)
{
    for (int i = 0; i < mine_list.size(); ++i)
    {
        if (mineHash(column, row) == mine_list[i])
            return true;
    }
    return false;
}

int board::begin_play(int column, int row)  //allows an end_game check after each play.
{
    int temp = play(column, row);
    if (temp == GAME_END_FAIL)
        return temp;
    int unvisited_mines = 0;
    int correct_flags = 0;
    for (int i = 0; i < columns; ++i)
        for(int j = 0; j < rows; ++j)
        {
            if (getState(i, j) == FLAG)
                return temp;
            else if (getState(i, j) == UNVISITED)
                return temp;
            else if (inMines(i, j) && getState(i, j) == FLAG)
                ++correct_flags;
            else if (inMines(i, j) && getState(i, j) == UNVISITED)
                ++unvisited_mines;
        }
    if (unvisited_mines + correct_flags == mines)
    {
        autoFlag();
        return GAME_END_SUCCESS;
    }
    return temp;
}

int board::mineHash(int column, int row)
{
    return (column * columns) + row;
}

int board::countMines(int column, int row)
{
    int adjacent_mines = 0;
    for (int i = -1; i < 2; ++i) //If no adjacent mines, play all cells around current cell.
    {
        for (int j = -1; j < 2; ++j)
        {
            if (i == 0 && j == 0) //If it's the same as the current cell
                continue;
            if (!inBounds(column + i, row + j))
                continue;
            if (inMines(column + i, row + j))
                ++adjacent_mines;
        }
    }
    return adjacent_mines;
}

int board::doubleClick(int column, int row)
{
    int game_state;
    if (getState(column, row) <= 0)
        return ONGOING;
    for (int i = -1; i < 2; ++i)
    {
        for (int j = -1; j < 2; ++j)
        {
            if (!inBounds(column + i, row + j))
                continue;
            if (i == 0 && j == 0)
                continue;
            if (getState(column + i, row + j) >= 0)
                continue;
            else if (getState(column + i, row + j) == UNVISITED)
            {
                game_state = begin_play(column + i, row + j);
                if (game_state == GAME_END_SUCCESS || game_state == GAME_END_FAIL)
                    return game_state;
            }
        }
    }
    return ONGOING;
}

int board::mark(int column, int row)
{
    if (getState(column, row) == UNVISITED)
    {
        setState(column, row, FLAG);
        ++flags;
    }
    else if (getState(column, row) == FLAG)
    {
        setState(column, row, QUESTION);
        --flags;
    }
    else if (getState(column, row) == QUESTION)
        setState(column, row, UNVISITED);

    if (flags == mines)
    {
        for (int i = 0; i < columns; ++i)
        {
            for (int j = 0; j < rows; ++j)
            {
                if (getState(i, j) == UNVISITED && inMines(i, j))
                    return ONGOING;
                if (getState(i, j) == FLAG && !inMines(i, j))
                    return ONGOING;
                if (getState(i, j) == QUESTION && inMines(i, j))
                    return ONGOING;
            }
        }
        return GAME_END_SUCCESS;
    }
    return ONGOING;
}

int board::play(int column, int row)
{
    int game_state;
    if (first_click)
    {
        int rand_row;
        int rand_column;
        int mine_count = 0;
        srand(time(NULL));
        while (mine_count < mines)
        {
            rand_row = rand() % rows;
            rand_column = rand() % columns;
            if (column == rand_column && row == rand_row) //prevents hitting mine on first click
                continue;
            if (inMines(rand_column, rand_row)) //prevents duplicate mines
                continue;
            mine_list.push_back(mineHash(rand_column, rand_row)); //add mines to list
            ++mine_count;
        }
        first_click = false;
    }

    if (getState(column, row) >= 0)
        return ONGOING;
    if (getState(column, row) == UNVISITED && inMines(column, row))
    {
        detonate(column, row);
        return GAME_END_FAIL;
    }
    if (getState(column, row) == FLAG && inMines(column, row))
    {
        detonate(column, row);
        return GAME_END_FAIL;
    }
    if (getState(column, row) == QUESTION && inMines(column, row))
    {
        detonate(column, row);
        return GAME_END_FAIL;
    }
    setState(column, row, countMines(column, row));
    if (getState(column, row) == 0)
    {
        for (int i = -1; i < 2; ++i)
        {
            for (int j = -1; j < 2; ++j)
            {
                if (i == 0 && j == 0)
                    continue;
                if (!inBounds(column + i, row + j))
                    continue;
                if (getState(column + i, row + j) == FLAG)
                    continue;
                if (getState(column + i, row + j) == QUESTION)
                    continue;
                game_state = play(column + i, row + j);
                if (game_state == GAME_END_SUCCESS)
                    return game_state;
                if (game_state == GAME_END_FAIL) //It shouldn't ever lose at this point, but just in case.
                    return game_state;
            }
        }
    }
    return ONGOING;
}

void board::autoFlag()
{
    for (int i = 0; i < columns; ++i)
        for (int j = 0; j < rows; ++j)
        {
            if(getState(i, j) == UNVISITED && inMines(i, j))
                setState(i, j, FLAG);
        }
}

void board::detonate(int column, int row)
{
    setState(column, row, DETONATE);
    for (int i = 0; i < columns; ++i)
    {
        for (int j = 0; j < rows; ++j)
        {
            if (getState(i, j) >= 0)
                continue;
            else if (getState(i, j) == FLAG && !inMines(i, j))
                setState(i, j, BAD_FLAG);
            else if (getState(i, j) == UNVISITED && inMines(i, j))
                setState(i, j, MINE);
            else if (getState(i, j) == QUESTION && inMines(i, j))
                setState(i, j, MINE);
            else if (getState(i, j) == QUESTION && !inMines(i, j))
                setState(i, j, BAD_QUESTION);
        }
    }
}

void board::setState(int column, int row, int state)
{
    game_board[column][row] = state;
}
