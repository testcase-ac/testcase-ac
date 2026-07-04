#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

static string randomRow(int side, double iProbability) {
    string row;
    row.reserve(side);
    for (int col = 0; col < side; ++col) {
        row.push_back(rnd.next() < iProbability ? 'I' : 'O');
    }
    return row;
}

static vector<string> makeRandomBoard(int n, double iProbability) {
    int side = 2 * n;
    vector<string> board;
    board.reserve(side);
    for (int row = 0; row < side; ++row) {
        board.push_back(randomRow(side, iProbability));
    }
    return board;
}

static vector<string> makeQuadrantBoard(int n, const vector<char>& quadrantChars) {
    int side = 2 * n;
    vector<string> board(side, string(side, 'O'));
    for (int row = 0; row < side; ++row) {
        for (int col = 0; col < side; ++col) {
            int quadrant = (row >= n) * 2 + (col >= n);
            board[row][col] = quadrantChars[quadrant];
        }
    }
    return board;
}

static vector<string> makePatternBoard(int n, int mode) {
    int side = 2 * n;
    vector<string> board(side, string(side, 'O'));
    for (int row = 0; row < side; ++row) {
        for (int col = 0; col < side; ++col) {
            bool isI = false;
            if (mode == 0) {
                isI = (row + col + rnd.next(0, 1)) % 2 == 0;
            } else if (mode == 1) {
                isI = (row < n) == (col < n);
            } else if (mode == 2) {
                isI = row == col || row + col + 1 == side;
            } else {
                isI = (row % 3) == (col % 3);
            }
            board[row][col] = isI ? 'I' : 'O';
        }
    }
    return board;
}

static void flipSomeCells(vector<string>& board, int flips) {
    int side = (int)board.size();
    for (int i = 0; i < flips; ++i) {
        int row = rnd.next(0, side - 1);
        int col = rnd.next(0, side - 1);
        board[row][col] = board[row][col] == 'I' ? 'O' : 'I';
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 7);
        int n;
        if (tc == 0) {
            n = 1;
        } else if (mode == 7) {
            n = rnd.next(20, 100);
        } else {
            n = rnd.next(1, 8);
        }

        vector<string> board;
        if (mode == 0) {
            board = makeQuadrantBoard(n, {'O', 'O', 'O', 'O'});
            flipSomeCells(board, rnd.next(0, min(4, 4 * n * n)));
        } else if (mode == 1) {
            board = makeQuadrantBoard(n, {'I', 'O', 'O', 'I'});
            flipSomeCells(board, rnd.next(0, min(2 * n, 10)));
        } else if (mode == 2) {
            board = makeQuadrantBoard(n, {'I', 'I', 'O', 'O'});
            flipSomeCells(board, rnd.next(0, min(3 * n, 12)));
        } else if (mode == 3) {
            board = makeQuadrantBoard(n, {'I', 'O', 'I', 'O'});
            flipSomeCells(board, rnd.next(0, min(3 * n, 12)));
        } else if (mode == 4) {
            board = makePatternBoard(n, rnd.next(0, 3));
            flipSomeCells(board, rnd.next(0, min(4 * n, 16)));
        } else if (mode == 5) {
            board = makeRandomBoard(n, rnd.next(0.05, 0.30));
        } else if (mode == 6) {
            board = makeRandomBoard(n, rnd.next(0.70, 0.95));
        } else {
            board = makeRandomBoard(n, rnd.next(0.35, 0.65));
        }

        println(n);
        for (const string& row : board) {
            println(row);
        }
    }

    return 0;
}
