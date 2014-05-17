#ifndef BOARD_H
#define BOARD_H

class board{
private:
    bool first_click;
    bool inBounds(int row, int column);
    int columns;
    int flags;
    int mines;
    int play(int, int);
    int rows;
    int countMines(int, int);
    int getState(int column, int row){return game_board[column][row];}
    void autoFlag();
    void detonate(int, int);
    void setState(int, int, int);

public:
    board(int, int, int);
    int begin_play(int, int);
    int doubleClick(int, int);
    int getColumns(){return columns;}
    int getRows(){return rows;}
    int mark(int, int);
    int** game_board;
    int** getArrayPointer(){return game_board;}
};

#endif // BOARD_H
