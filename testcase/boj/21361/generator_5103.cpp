#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Dimensions
    int R = rnd.next(3, 10);
    int C = rnd.next(3, 10);
    // Command length
    int N = rnd.next(1, 20);

    // Hyper-parameter for obstacle density bias
    int t = rnd.next(-1, 1);
    double density = rnd.wnext(100, t) / 100.0;

    // Initialize grid with border '#' and interior '.'
    vector<string> grid(R, string(C, '.'));
    for (int i = 0; i < R; i++) {
        grid[i][0] = grid[i][C-1] = '#';
    }
    for (int j = 0; j < C; j++) {
        grid[0][j] = grid[R-1][j] = '#';
    }

    // Place interior obstacles
    for (int i = 1; i < R-1; i++) {
        for (int j = 1; j < C-1; j++) {
            if (rnd.next() < density)
                grid[i][j] = '#';
        }
    }

    // Collect empty interior cells
    vector<pair<int,int>> empties;
    for (int i = 1; i < R-1; i++)
        for (int j = 1; j < C-1; j++)
            if (grid[i][j] == '.')
                empties.emplace_back(i, j);

    // Ensure at least one starting cell
    if (empties.empty()) {
        int i = rnd.next(1, R-2);
        int j = rnd.next(1, C-2);
        grid[i][j] = '.';
        empties.emplace_back(i, j);
    }

    // Choose start position
    auto [si, sj] = rnd.any(empties);
    grid[si][sj] = 'O';

    // Generate command string
    const string dirs = "^>v<";
    string cmds;
    cmds.reserve(N);
    for (int i = 0; i < N; i++) {
        cmds.push_back(rnd.any(dirs));
    }

    // Output
    println(R, C, N);
    println(cmds);
    for (auto &row : grid)
        println(row);

    return 0;
}
