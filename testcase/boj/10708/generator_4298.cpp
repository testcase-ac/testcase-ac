#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of friends and games
    int N = rnd.next(3, 10);
    int M = rnd.next(3, 10);

    // Choose targets for each game
    vector<int> A(M);
    for (int i = 0; i < M; i++) {
        A[i] = rnd.next(1, N);
    }

    // Build the guess matrix B: M games × N friends
    vector<vector<int>> B(M, vector<int>(N));
    for (int i = 0; i < M; i++) {
        int target = A[i];
        // Game type: 0 = everyone correct, 1 = everyone wrong (except target),
        // 2 = mixed with random probability
        int type = rnd.next(0, 2);
        double p = rnd.next();  // used if type == 2
        // Precompute non-target choices
        vector<int> others;
        for (int x = 1; x <= N; x++) {
            if (x != target) others.push_back(x);
        }
        for (int j = 1; j <= N; j++) {
            if (j == target) {
                // target always writes their own name
                B[i][j-1] = target;
            } else {
                if (type == 0) {
                    // everyone guesses the target
                    B[i][j-1] = target;
                } else if (type == 1) {
                    // everyone guesses wrong (anyone but the target)
                    B[i][j-1] = rnd.any(others);
                } else {
                    // mixed behavior
                    if (rnd.next() < p) {
                        B[i][j-1] = target;
                    } else {
                        B[i][j-1] = rnd.any(others);
                    }
                }
            }
        }
    }

    // Output in the required format
    println(N);
    println(M);
    println(A);
    for (int i = 0; i < M; i++) {
        println(B[i]);
    }

    return 0;
}
