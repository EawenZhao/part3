#include "application.h"
#include <iostream>

using namespace std;


//board
int board[8][8] = {0};
//Total queen number
int queenNum = 0;
//
int done = 0;


void Application::initialize() {
}

Position Application::getStartPosition() {
    board[0][0] = 1;
    return Position(0, 0);
}

bool Application::isValid(const Position &p) {
    int row = p.getRow();
    int column = p.getColumn();
    bool check_row = false;
    bool check_column = false;
    bool check_diag = false;

    for (int i = 0; i < 8; ++i) {
        if (board[i][column] == 1) {
            check_row = true;
        }
    }   // check for column

    for (int i = 0; i < 8; ++i) {
        if (board[row][i] == 1) {
            check_column = true;
        }
    }   //check for row

    for (int i = 0; i < 8; i++) //check for diag
    {
        for (int j = 0; j < 8; j++) {
            if (i == row && j == column) { continue; }
            if (abs(i - row) == abs(j - column)) {
                if (board[i][j] == 1) { check_diag = true; }
            }
        }
    }


    return (row >= 0 && row <= 7) && (column >= 0 && column <= 7)
           && !(check_column || check_diag || check_row);
}

void Application::progress(const Position &p) {
    queenNum++;
    board[p.getRow()][p.getColumn()] = 1;
    done = 0;
}

bool Application::success(const Position &p) {
    return queenNum == 8;
}


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
    int row = ((itrPosition *) currItrPosPtr)->row;   //（ ）是类型强转
    int column = ((itrPosition *) currItrPosPtr)->column;
    // Check whether an application has been created


    if (done == 0) {
        row = 0;
        column++;
        done = 1;
    } else { row++; }



    //return the current postion data back to the iterator
    ((itrPosition *) currItrPosPtr)->row = row;
    ((itrPosition *) currItrPosPtr)->column = column;
    return Position(row, column); //return the new position
}

bool Application::Iterator::noNextPosition() {
    return ((itrPosition *) currItrPosPtr)->row == 8;
}

Application::Iterator::~Iterator() {
    delete (itrPosition *) currItrPosPtr;
}