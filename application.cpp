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

/******** To be implemented ↓ **********/
bool Application::isValid(const Position &p) {
    int row = p.getRow();
    int column = p.getColumn();
    return (row >= 0 && row <= 7) && (column >= 0 && column <= 7) && ;
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
    int turn;
    /******* What does this 'turn' mean ↑ ? ************/
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
    p->turn = 0;
    currItrPosPtr = p;
    //current-iterator-position pointer
}

Position Application::Iterator::getNextPosition() {
    int row = ((itrPosition *) currItrPosPtr)->row;   //（ ）是类型强转
    int column = ((itrPosition *) currItrPosPtr)->column;
    int turn = ((itrPosition *) currItrPosPtr)->turn;
    if (turn == 0) {
        column++;
        turn++;
    } else if (turn == 1) {
        row++;
        turn++;
    } else if (turn == 2) {
        column--;
        turn++;
    } else if (turn == 3) {
        row--;
        turn++;
    } else {
    }
    ((itrPosition *) currItrPosPtr)->turn = turn;
    return Position(row, column); //return the new position
}

bool Application::Iterator::noNextPosition() {
    return ((itrPosition *) currItrPosPtr)->turn > 3;
}

Application::Iterator::~Iterator() {
    delete (itrPosition *) currItrPosPtr;
}