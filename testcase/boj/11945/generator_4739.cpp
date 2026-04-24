#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Always at least one row and one column to avoid blank lines issues
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);

    // Hyper-parameters for diversity
    double density   = rnd.next(0.0, 1.0);
    double blockProb = rnd.next(0.0, 1.0);
    double checkerProb = rnd.next(0.0, 1.0);

    // Initialize grid of '0's
    vector<string> grid(N, string(M, '0'));

    // Option 1: solid block of '1's plus sparse fill
    if (rnd.next() < blockProb) {
        int r1 = rnd.next(0, N - 1);
        int r2 = rnd.next(r1, N - 1);
        int c1 = rnd.next(0, M - 1);
        int c2 = rnd.next(c1, M - 1);
        for (int i = r1; i <= r2; ++i)
            for (int j = c1; j <= c2; ++j)
                grid[i][j] = '1';
        double q = density * 0.5;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                if (grid[i][j] == '0' && rnd.next() < q)
                    grid[i][j] = '1';
    }
    // Option 2: checkerboard pattern
    else if (rnd.next() < checkerProb * 0.5) {
        bool startWithOne = rnd.next() < 0.5;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                grid[i][j] = (((i + j) % 2 == 0) == startWithOne ? '1' : '0');
    }
    // Option 3: pure random fill
    else {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                if (rnd.next() < density)
                    grid[i][j] = '1';
    }

    // Ensure at least one '1' and one '0' to avoid extreme edge cases
    bool has1 = false, has0 = false;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j) {
            has1 |= (grid[i][j] == '1');
            has0 |= (grid[i][j] == '0');
        }
    if (!has1) {
        int i = rnd.next(0, N - 1), j = rnd.next(0, M - 1);
        grid[i][j] = '1';
    }
    if (!has0) {
        int i = rnd.next(0, N - 1), j = rnd.next(0, M - 1);
        grid[i][j] = '0';
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; ++i)
        printf("%s\n", grid[i].c_str());

    return 0;
}
