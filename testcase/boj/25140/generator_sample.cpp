#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

static int inversionParity(const vector<string>& board) {
    vector<int> values;
    for (const string& cell : board) {
        if (cell != "X") {
            values.push_back(cell[0] - '0');
        }
    }

    int inversions = 0;
    for (int i = 0; i < (int)values.size(); ++i) {
        for (int j = i + 1; j < (int)values.size(); ++j) {
            if (values[i] > values[j]) {
                ++inversions;
            }
        }
    }
    return inversions % 2;
}

static vector<string> scrambledBoard(int moves) {
    vector<string> board = {"1", "2", "3", "4", "5", "6", "7", "8", "X"};
    int blank = 8;
    int previous = -1;

    for (int step = 0; step < moves; ++step) {
        vector<int> options;
        int row = blank / 3;
        int col = blank % 3;

        if (row > 0) options.push_back(blank - 3);
        if (row < 2) options.push_back(blank + 3);
        if (col > 0) options.push_back(blank - 1);
        if (col < 2) options.push_back(blank + 1);

        if (options.size() > 1) {
            options.erase(remove(options.begin(), options.end(), previous), options.end());
        }

        int next = rnd.any(options);
        swap(board[blank], board[next]);
        previous = blank;
        blank = next;
    }

    return board;
}

static vector<string> randomSolvableBoard() {
    vector<string> board = {"1", "2", "3", "4", "5", "6", "7", "8", "X"};
    shuffle(board.begin(), board.end());

    if (inversionParity(board) != 0) {
        int first = -1;
        int second = -1;
        for (int i = 0; i < (int)board.size(); ++i) {
            if (board[i] != "X") {
                if (first == -1) {
                    first = i;
                } else {
                    second = i;
                    break;
                }
            }
        }
        swap(board[first], board[second]);
    }

    return board;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    vector<string> board;
    if (mode == 0) {
        board = scrambledBoard(rnd.next(0, 4));
    } else if (mode == 1) {
        board = scrambledBoard(rnd.next(5, 14));
    } else if (mode == 2) {
        board = scrambledBoard(rnd.next(15, 40));
    } else {
        board = randomSolvableBoard();
    }

    for (int row = 0; row < 3; ++row) {
        println(board[row * 3], board[row * 3 + 1], board[row * 3 + 2]);
    }

    return 0;
}
