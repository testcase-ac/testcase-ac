#include "testlib.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameters
    int min_N = 4;
    int max_N = 10; // Reduced max_N for easier verification
    double zero_prob = rnd.next(0.1, 0.5); // Probability of a cell being zero (excluding the bottom-right)
    int max_val = 9;

    int N = rnd.next(min_N, max_N);

    cout << N << endl;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == N - 1 && j == N - 1) {
                cout << 0;
            } else {
                if (rnd.next() < zero_prob) {
                    cout << 0;
                } else {
                    cout << rnd.next(1, max_val);
                }
            }
            if (j < N - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
