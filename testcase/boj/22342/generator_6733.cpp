#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Generate dimensions with edge-case bias
    int M, N;
    if (rnd.next(0, 9) == 0) {
        // 10% chance N=1
        N = 1;
        M = rnd.next(1, 15);
    } else if (rnd.next(0, 9) == 0) {
        // 10% chance M=1
        M = 1;
        N = rnd.next(1, 15);
    } else {
        // general case with weighted distribution
        int wM = rnd.next(-1, 1);
        int wN = rnd.next(-1, 1);
        M = rnd.wnext(15, wM) + 1;  // [1..15]
        N = rnd.wnext(15, wN) + 1;  // [1..15]
    }

    // Prepare grid
    vector<string> grid(M, string(N, '0'));
    int pattern = rnd.next(0, 2);
    if (pattern == 0) {
        // Uniform random weights
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                grid[i][j] = char('0' + rnd.next(1, 9));
            }
        }
    } else if (pattern == 1) {
        // Gradient pattern with occasional noise
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                int v = ((i + 1) * (j + 1)) % 9 + 1;
                grid[i][j] = char('0' + v);
            }
        }
        // add some random noise
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (rnd.next(0, 4) == 0) {
                    grid[i][j] = char('0' + rnd.next(1, 9));
                }
            }
        }
    } else {
        // Horizontal stripe pattern
        for (int i = 0; i < M; i++) {
            bool high = rnd.next(0, 1);
            for (int j = 0; j < N; j++) {
                if (high) grid[i][j] = char('0' + rnd.next(5, 9));
                else      grid[i][j] = char('0' + rnd.next(1, 5));
            }
        }
    }

    // Output
    println(M, N);
    for (auto &row : grid) {
        println(row);
    }
    return 0;
}
