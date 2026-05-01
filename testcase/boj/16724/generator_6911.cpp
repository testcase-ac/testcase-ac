#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Ensure at least 2 cells so every cell can point to a neighbor
    int N, M;
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        // Single row case
        N = 1;
        M = rnd.next(2, 10);
    } else if (mode == 1) {
        // Single column case
        M = 1;
        N = rnd.next(2, 10);
    } else {
        // General case
        N = rnd.next(2, 10);
        M = rnd.next(2, 10);
    }
    vector<string> grid(N, string(M, '?'));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            string opts;
            if (i > 0)      opts.push_back('U');
            if (i + 1 < N)  opts.push_back('D');
            if (j > 0)      opts.push_back('L');
            if (j + 1 < M)  opts.push_back('R');
            // Uniform choice among valid directions
            grid[i][j] = rnd.any(opts);
        }
    }
    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        println(grid[i]);
    }
    return 0;
}
