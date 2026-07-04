#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

namespace {

const int kGoal[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
const int kNeighbors[9][4] = {
    {1, 3, -1, -1}, {0, 2, 4, -1}, {1, 5, -1, -1},
    {0, 4, 6, -1}, {1, 3, 5, 7}, {2, 4, 8, -1},
    {3, 7, -1, -1}, {4, 6, 8, -1}, {5, 7, -1, -1},
};

vector<int> randomWalk(int steps) {
    vector<int> board(kGoal, kGoal + 9);
    int zero = 8;
    int previous = -1;

    for (int step = 0; step < steps; ++step) {
        vector<int> choices;
        for (int i = 0; i < 4; ++i) {
            int next = kNeighbors[zero][i];
            if (next != -1 && next != previous) choices.push_back(next);
        }

        int next = rnd.any(choices);
        swap(board[zero], board[next]);
        previous = zero;
        zero = next;
    }

    return board;
}

void makeUnsolvable(vector<int>& board) {
    vector<int> positions;
    for (int i = 0; i < 9; ++i) {
        if (board[i] != 0) positions.push_back(i);
    }

    int a = rnd.next(static_cast<int>(positions.size()));
    int b = rnd.next(static_cast<int>(positions.size() - 1));
    if (b >= a) ++b;
    swap(board[positions[a]], board[positions[b]]);
}

void printBoard(const vector<int>& board) {
    for (int row = 0; row < 3; ++row) {
        println(board[row * 3], board[row * 3 + 1], board[row * 3 + 2]);
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<int> board;

    if (mode == 0) {
        board.assign(kGoal, kGoal + 9);
        int swaps = rnd.next(1, 20);
        while (swaps--) {
            int a = rnd.next(9);
            int b = rnd.next(8);
            if (b >= a) ++b;
            swap(board[a], board[b]);
        }
    } else {
        int steps = 0;
        if (mode == 1) steps = rnd.next(0, 4);
        if (mode == 2) steps = rnd.next(5, 20);
        if (mode >= 3) steps = rnd.next(21, 80);
        board = randomWalk(steps);

        if (mode == 4) makeUnsolvable(board);
    }

    printBoard(board);
    return 0;
}
