#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for N and M skew
    vector<int> twOptions = {-2, -1, 1, 2};
    int twN = rnd.any(twOptions);
    int twM = rnd.any(twOptions);
    // N, M in [1..10], with bias
    int N = rnd.wnext(10, twN) + 1;
    int M = rnd.wnext(10, twM) + 1;

    // Choose pattern of candy distribution: 0=random, 1=uniform, 2=gradient+noise
    int pattern = rnd.next(0, 2);

    vector<vector<int>> grid(N, vector<int>(M, 0));
    if (pattern == 1) {
        // uniform candies
        int x = rnd.next(0, 100);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                grid[i][j] = x;
    } else if (pattern == 2) {
        // gradient with noise
        int factor = rnd.next(1, 5);
        int noiseLevel = rnd.next(0, 5);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                int base = (i + 1) + (j + 1);
                int noise = rnd.next(-noiseLevel, noiseLevel);
                int val = base * factor + noise;
                if (val < 0) val = 0;
                if (val > 100) val = 100;
                grid[i][j] = val;
            }
        }
    } else {
        // purely random up to a max
        int maxCandy = rnd.next(0, 100);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                grid[i][j] = rnd.next(0, maxCandy);
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        println(grid[i]);
    }
    return 0;
}
