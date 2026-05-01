#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Dimensions
    int N = rnd.next(1, 12);
    int M = rnd.next(1, 12);

    // Time T: usually small, occasionally large
    int T = (rnd.next(0, 3) == 0 ? rnd.next(1, 300) : rnd.next(1, 20));

    // Neighborhood radius K (must be at least 1)
    int maxKM = max(N, M);
    int K = rnd.next(1, maxKM);

    // Compute neighbor count bounds
    int totalNbr = (2 * K + 1) * (2 * K + 1) - 1;
    int a = rnd.next(0, totalNbr);
    int b = rnd.next(a, totalNbr);

    // Generate initial grid
    vector<string> grid(N, string(M, '.'));
    int mode = rnd.next(0, 3);
    if (mode == 1) {
        // full of life
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                grid[i][j] = '*';
    } else if (mode == 2) {
        // random density
        int den = rnd.next(0, 100);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (rnd.next(100) < den)
                    grid[i][j] = '*';
    }
    // mode 0: all dead

    // Output
    println(N, M, T);
    println(K, a, b);
    for (auto &row : grid)
        println(row);

    return 0;
}
