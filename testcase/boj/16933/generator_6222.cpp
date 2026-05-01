#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small grid sizes for manual verification
    int N = rnd.next(1, 8);
    int M = rnd.next(1, 8);
    int K = rnd.next(1, min(3, 10));

    // Choose a generation pattern for variability
    int pattern = rnd.next(0, 2);
    if (pattern == 2 && (N == 1 || M == 1)) {
        // Avoid complex path on 1D grids
        pattern = 1;
    }

    // Initialize all cells as open
    vector<string> grid(N, string(M, '0'));

    if (pattern == 0) {
        // Pattern 0: Empty grid (no walls)
        // Already all '0's
    }
    else if (pattern == 1) {
        // Pattern 1: Random walls with moderate density
        double density = rnd.next(0.3, 0.7);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if ((i == 0 && j == 0) || (i == N - 1 && j == M - 1))
                    continue;
                if (rnd.next() < density)
                    grid[i][j] = '1';
            }
        }
    }
    else {
        // Pattern 2: Guarantee a simple path then add sparse walls
        vector<pair<int,int>> path;
        int x = 0, y = 0;
        path.emplace_back(x, y);
        // Walk greedily towards (N-1, M-1)
        while (x != N - 1 || y != M - 1) {
            bool horiz = rnd.next(0.0, 1.0) < 0.5;
            if (horiz) {
                if (y < M - 1) y++;
                else if (x < N - 1) x++;
                else y = min(y + 1, M - 1);
            } else {
                if (x < N - 1) x++;
                else if (y < M - 1) y++;
                else x = min(x + 1, N - 1);
            }
            path.emplace_back(x, y);
        }
        // Fill entire grid with walls
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                grid[i][j] = '1';
        // Carve out the path
        for (auto &p : path)
            grid[p.first][p.second] = '0';
        // Randomly open some extra cells
        double p_open = rnd.next(0.0, 0.2);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if ((i == 0 && j == 0) || (i == N - 1 && j == M - 1))
                    continue;
                if (grid[i][j] == '1' && rnd.next() < p_open)
                    grid[i][j] = '0';
            }
        }
    }

    // Ensure start and end are open
    grid[0][0] = '0';
    grid[N-1][M-1] = '0';

    // Output the generated test case
    println(N, M, K);
    for (int i = 0; i < N; i++)
        println(grid[i]);

    return 0;
}
