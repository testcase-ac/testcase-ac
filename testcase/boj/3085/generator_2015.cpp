#include "testlib.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose board dimensions in [3, 8] for an easily verifiable testcase.
    int N = rnd.next(3, 8);
    
    // Available candy colors: C (red), P (blue), Z (green), Y (yellow)
    string candies = "CPZY";
    vector<string> board(N, string(N, ' '));

    // Hyperparameter: With some probability, bias one candy to appear more frequently.
    bool useBias = rnd.next(0, 1); // 50% chance to use bias distribution.
    char biasedCandy = candies[rnd.next(0, 3)];
    // Bias strength: probability to use biasedCandy vs uniform.
    double biasProb = rnd.next(0.3, 0.8); // bias probability between 0.3 and 0.8

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (useBias && rnd.next(0.0, 1.0) < biasProb) {
                board[i][j] = biasedCandy;
            } else {
                board[i][j] = candies[rnd.next(0, 3)];
            }
        }
    }

    // Guarantee that the board is not uniform.
    bool allSame = true;
    for (int i = 0; i < N && allSame; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] != board[0][0]) {
                allSame = false;
                break;
            }
        }
    }
    if(allSame) {
        // Change a random cell (other than the first one) to a different candy.
        int i = rnd.next(0, N - 1);
        int j = rnd.next(0, N - 1);
        char current = board[i][j];
        char newCandy;
        do {
            newCandy = candies[rnd.next(0, 3)];
        } while(newCandy == current);
        board[i][j] = newCandy;
    }
    
    // Output the test case using testlib's println.
    println(N);
    for (int i = 0; i < N; i++) {
        println(board[i]);
    }
    
    return 0;
}
