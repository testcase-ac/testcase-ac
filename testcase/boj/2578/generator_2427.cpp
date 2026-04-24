/* generator code */
#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate a random bingo board (5x5) with numbers 1..25
    vector<int> board(25);
    iota(board.begin(), board.end(), 1);
    shuffle(board.begin(), board.end());
    for (int i = 0; i < 5; i++) {
        println(board[i*5 + 0], board[i*5 + 1], board[i*5 + 2], board[i*5 + 3], board[i*5 + 4]);
    }

    // Generate a random call sequence (also a permutation of 1..25)
    vector<int> calls(25);
    iota(calls.begin(), calls.end(), 1);
    shuffle(calls.begin(), calls.end());
    for (int i = 0; i < 5; i++) {
        println(calls[i*5 + 0], calls[i*5 + 1], calls[i*5 + 2], calls[i*5 + 3], calls[i*5 + 4]);
    }

    return 0;
}
