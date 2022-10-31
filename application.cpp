#include "application.h"
#include <iostream>

using namespace std;


//board
char board[8][8] = {0};
int queenNum = 0;

void Application::initialize() {
}

Position Application::getStartPosition() {
    board[0][0] = 'Q';
    return Position(0, 0);
}

bool Application::isValid(const Position &p) {
    int row = p.getRow();
    int column = p.getColumn();
    bool check_row = false;
    bool check_column = false;
    bool check_diag = false;

    for (int i = 0; i < 8; ++i) {
        if (board[i][column] == 'Q') {
            check_row = true;
        }
    }   // check for column

    for (int i = 0; i < 8; ++i) {
        if (board[row][i] == 'Q') {
            check_column = true;
        }
    }   //check for row

    if (board[row - 1][column - 1] == 'Q' || board[row + 1][column + 1] == 'Q' ||
        board[row - 1][column + 1] == 'Q' || board[row + 1][column - 1] == 'Q') {
        check_diag = true;
    }//check for diag


    return (row >= 0 && row <= 7) && (column >= 0 && column <= 7)
           && !(check_column || check_diag || check_row);
}

void Application::progress(const Position &p) {
    board[p.getRow()][p.getColumn()] = 'Q';
    queenNum++;
}

bool Application::success(const Position &p) {
    return queenNum == 8;
}

/******** maybe ********/

void Application::goBack(const Position &p) {

    board[p.getRow()][p.getColumn()] = 0;
    queenNum--;
}

void Application::print() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}


//======================================================================
struct itrPosition {
    int row;
    int column;
};

//application iterator
Application::Iterator::Iterator() {
    currItrPosPtr = NULL;
    //current-iterator-position pointer
}

Application::Iterator::Iterator(const Position &currPos) {
    itrPosition *p = new itrPosition;
    p->row = currPos.getRow();
    p->column = currPos.getColumn();
    currItrPosPtr = p;
    //current-iterator-position pointer
}

Position Application::Iterator::getNextPosition() {
    static int done = 0;
    static int row = ((itrPosition *) currItrPosPtr)->row;   //（ ）是类型强转
    static int column = ((itrPosition *) currItrPosPtr)->column;
    if (done == 0) {
        column++;
        done = 1;
    } else { row++; }

    return Position(row, column); //return the new position
}

bool Application::Iterator::noNextPosition() {
    return ((itrPosition *) currItrPosPtr)->row == 7;
}

Application::Iterator::~Iterator() {
    delete (itrPosition *) currItrPosPtr;
}