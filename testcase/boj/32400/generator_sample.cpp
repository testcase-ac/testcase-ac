#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> board(20);
    iota(board.begin(), board.end(), 1);
    shuffle(board.begin(), board.end());

    int mode = rnd.next(0, 5);
    if (mode != 5) {
        vector<pair<int, int>> neighborPairs = {
            {1, 2},    // Bob by a wide margin.
            {5, 6},    // Bob just below Alice's threshold.
            {5, 7},    // Alice just above the threshold.
            {18, 19},  // Alice by a wide margin.
            {1, 19},   // Mixed extremes around 20.
        };

        int center = rnd.next(0, 19);
        int left = (center + 19) % 20;
        int right = (center + 1) % 20;
        pair<int, int> neighbors = neighborPairs[mode];
        if (rnd.next(0, 1)) {
            swap(neighbors.first, neighbors.second);
        }

        vector<int> rest;
        for (int x = 1; x <= 20; ++x) {
            if (x != 20 && x != neighbors.first && x != neighbors.second) {
                rest.push_back(x);
            }
        }
        shuffle(rest.begin(), rest.end());

        board.assign(20, 0);
        board[center] = 20;
        board[left] = neighbors.first;
        board[right] = neighbors.second;

        int at = 0;
        for (int i = 0; i < 20; ++i) {
            if (board[i] == 0) {
                board[i] = rest[at++];
            }
        }
    }

    println(board);
    return 0;
}
