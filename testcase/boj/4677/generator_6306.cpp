#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of test cases
    int G = rnd.next(2, 6);
    // directions for 8-neighbors
    int dx[8] = {-1,-1,-1,0,0,1,1,1};
    int dy[8] = {-1,0,1,-1,1,-1,0,1};

    for (int t = 0; t < G; ++t) {
        // choose small grid with area <= 200
        int m, n;
        do {
            m = rnd.next(1, 20);
            n = rnd.next(1, 20);
        } while (m * n > 200);
        vector<string> grid(m, string(n, '*'));

        // assemble valid modes
        vector<int> modes = {0, 2, 3, 4, 5, 6};
        if (m * n <= 100) modes.push_back(1);
        int mode = rnd.any(modes);

        // mode 0: empty grid
        if (mode == 0) {
            // already all '*'
        }
        // mode 1: full grid of '@'
        else if (mode == 1) {
            for (int i = 0; i < m; ++i)
                grid[i] = string(n, '@');
        }
        // mode 2: single connected cluster up to 100
        else if (mode == 2) {
            int maxCluster = min(m * n, 100);
            int target = rnd.next(1, maxCluster);
            int sr = rnd.next(0, m - 1);
            int sc = rnd.next(0, n - 1);
            vector<vector<bool>> in_cl(m, vector<bool>(n, false));
            vector<vector<bool>> in_fr(m, vector<bool>(n, false));
            vector<pair<int,int>> frontier;
            in_cl[sr][sc] = true;
            frontier.reserve(target * 4);
            // seed neighbors
            for (int d = 0; d < 8; ++d) {
                int ni = sr + dx[d], nj = sc + dy[d];
                if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
                    frontier.emplace_back(ni, nj);
                    in_fr[ni][nj] = true;
                }
            }
            int placed = 1;
            while (placed < target && !frontier.empty()) {
                int idx = rnd.next(0, (int)frontier.size() - 1);
                auto p = frontier[idx];
                frontier.erase(frontier.begin() + idx);
                int pi = p.first, pj = p.second;
                if (in_cl[pi][pj]) continue;
                in_cl[pi][pj] = true;
                ++placed;
                // expand frontier
                for (int d = 0; d < 8; ++d) {
                    int ni = pi + dx[d], nj = pj + dy[d];
                    if (ni >= 0 && ni < m && nj >= 0 && nj < n
                        && !in_cl[ni][nj] && !in_fr[ni][nj]) {
                        frontier.emplace_back(ni, nj);
                        in_fr[ni][nj] = true;
                    }
                }
            }
            // mark grid
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < n; ++j)
                    if (in_cl[i][j]) grid[i][j] = '@';
        }
        // mode 3: random sparse fill
        else if (mode == 3) {
            vector<double> dens = {0.05, 0.1, 0.2, 0.3};
            double density = rnd.any(dens);
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (rnd.next() < density) grid[i][j] = '@';
                }
            }
        }
        // mode 4: checkerboard pattern
        else if (mode == 4) {
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < n; ++j)
                    if ((i + j) % 2 == 0)
                        grid[i][j] = '@';
        }
        // mode 5: stripes
        else if (mode == 5) {
            bool horiz = rnd.next(0,1) == 0;
            if (horiz) {
                for (int i = 0; i < m; ++i)
                    if (i % 2 == 0) grid[i] = string(n, '@');
            } else {
                for (int i = 0; i < m; ++i)
                    for (int j = 0; j < n; ++j)
                        if (j % 2 == 0) grid[i][j] = '@';
            }
        }
        // mode 6: diagonal chain
        else if (mode == 6) {
            int L = min(m, n);
            for (int k = 0; k < L; ++k)
                grid[k][k] = '@';
        }

        // output
        println(m, n);
        for (int i = 0; i < m; ++i)
            println(grid[i]);
    }
    // termination
    println(0, 0);
    return 0;
}
