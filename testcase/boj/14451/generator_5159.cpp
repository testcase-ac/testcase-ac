#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid size hyper-parameter
    int N = rnd.next(2, 10);

    // Build a guaranteed simple up-right path from start to goal
    // Start at bottom-left (r=N-1, c=0), goal at top-right (r=0, c=N-1)
    vector<int> moves; // 0 = up, 1 = right
    for (int i = 0; i < N-1; i++) moves.push_back(0);
    for (int i = 0; i < N-1; i++) moves.push_back(1);
    shuffle(moves.begin(), moves.end());

    vector<vector<bool>> inPath(N, vector<bool>(N, false));
    int r = N-1, c = 0;
    inPath[r][c] = true;
    for (int mv : moves) {
        if (mv == 0) r--; else c++;
        inPath[r][c] = true;
    }

    // Collect other cells outside the guaranteed path
    vector<pair<int,int>> others;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!inPath[i][j]) others.emplace_back(i, j);
        }
    }

    // Hyper-parameter to vary obstacle density: weighted next on count of other cells
    int t = rnd.next(-2, 2);
    int M = rnd.wnext((int)others.size() + 1, t);
    shuffle(others.begin(), others.end());

    // Build grid, mark path as empty, place M obstacles in other cells
    vector<string> grid(N, string(N, 'E'));
    for (int i = 0; i < M; i++) {
        auto pr = others[i];
        grid[pr.first][pr.second] = 'H';
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        printf("%s\n", grid[i].c_str());
    }

    return 0;
}
