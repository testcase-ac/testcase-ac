#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

void addMove(string& moves, int& row, int& col, char move) {
    if (move == 'U') {
        --row;
    } else if (move == 'D') {
        ++row;
    } else if (move == 'L') {
        --col;
    } else {
        ++col;
    }
    moves.push_back(move);
}

vector<char> validMoves(int n, int row, int col) {
    vector<char> moves;
    if (row > 0) moves.push_back('U');
    if (row + 1 < n) moves.push_back('D');
    if (col > 0) moves.push_back('L');
    if (col + 1 < n) moves.push_back('R');
    return moves;
}

void randomWalk(string& moves, int n, int& row, int& col, int targetLength) {
    while ((int)moves.size() < targetLength) {
        vector<char> options = validMoves(n, row, col);
        addMove(moves, row, col, rnd.any(options));
    }
}

void appendRepeated(string& moves, int& row, int& col, char move, int count) {
    for (int i = 0; i < count; ++i) {
        addMove(moves, row, col, move);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 25);
    int row = 0;
    int col = 0;
    string moves;

    if (mode == 0) {
        int targetLength = rnd.next(1, 80);
        randomWalk(moves, n, row, col, targetLength);
    } else if (mode == 1) {
        int down = rnd.next(1, n - 1);
        int right = rnd.next(0, n - 1);
        appendRepeated(moves, row, col, 'D', down);
        appendRepeated(moves, row, col, 'R', right);
        int up = rnd.next(0, row);
        int left = rnd.next(0, col);
        appendRepeated(moves, row, col, 'U', up);
        appendRepeated(moves, row, col, 'L', left);
        int currentLength = (int)moves.size();
        randomWalk(moves, n, row, col,
                   rnd.next(currentLength, max(currentLength, 80)));
    } else if (mode == 2) {
        int width = rnd.next(1, n - 1);
        int height = rnd.next(1, n - 1);
        int loops = rnd.next(1, 4);
        for (int i = 0; i < loops; ++i) {
            appendRepeated(moves, row, col, 'R', width);
            appendRepeated(moves, row, col, 'D', height);
            appendRepeated(moves, row, col, 'L', width);
            appendRepeated(moves, row, col, 'U', height);
        }
    } else if (mode == 3) {
        int steps = rnd.next(1, min(n - 1, 12));
        for (int i = 0; i < steps; ++i) {
            addMove(moves, row, col, 'D');
            addMove(moves, row, col, 'R');
        }
        randomWalk(moves, n, row, col, rnd.next((int)moves.size(), 90));
    } else {
        n = rnd.next(50000, 100000);
        int down = rnd.next(1, 40);
        int right = rnd.next(1, 40);
        appendRepeated(moves, row, col, 'D', down);
        appendRepeated(moves, row, col, 'R', right);
        randomWalk(moves, n, row, col, rnd.next((int)moves.size(), 120));
    }

    println(n, (int)moves.size());
    println(moves);

    return 0;
}
