#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Grid size N between 3 and 16
    int N = rnd.next(3, 16);
    // Hyper-parameter for obstacle density skew: t<0 favors low density, t>0 favors high density
    int t = rnd.next(-3, 3);
    int densityPct = rnd.wnext(50, t); // 0..49
    double density = densityPct / 100.0;
    // Sometimes block the end cell to force zero-answer cases
    bool blockEnd = rnd.next(0, 1) == 0;

    vector<vector<int>> grid(N, vector<int>(N, 0));
    // Fill random obstacles based on density
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            // Ensure starting pipe cells are empty: (1,1)->(0,0) and (1,2)->(0,1)
            if ((i == 0 && j == 0) || (i == 0 && j == 1)) continue;
            if (rnd.next() < density) grid[i][j] = 1;
        }
    }
    if (blockEnd) {
        grid[N-1][N-1] = 1; // block the target cell
    }

    // Output
    println(N);
    for (auto &row : grid) {
        println(row);
    }
    return 0;
}
