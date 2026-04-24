#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of test cases
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Hyper-parameter: grid size with weighted randomness
        int tH = rnd.next(-1, 1);
        int tW = rnd.next(-1, 1);
        int H = rnd.wnext(11, tH) + 1; // in [1,11]
        int W = rnd.wnext(11, tW) + 1; // in [1,11]
        vector<string> grid(H, string(W, '.'));
        // collect all cells
        vector<pair<int,int>> empties;
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                empties.emplace_back(i, j);
        shuffle(empties.begin(), empties.end());
        int letterIdx = 0;
        double startProb = rnd.next(); // base probability for starting shapes

        // attempt to place shapes
        for (int idx = 0; idx < (int)empties.size() && letterIdx < 26; idx++) {
            int r0 = empties[idx].first, c0 = empties[idx].second;
            if (grid[r0][c0] != '.') continue;
            // force at least one shape
            if (letterIdx == 0 || rnd.next() < startProb) {
                int maxSize = min(5, H * W);
                int S = rnd.next(1, maxSize);
                vector<pair<int,int>> shape;
                shape.emplace_back(r0, c0);
                grid[r0][c0] = '?'; // mark temporarily
                // grow the shape
                for (int step = 1; step < S; step++) {
                    vector<pair<int,int>> cand;
                    for (auto &p : shape) {
                        int x = p.first, y = p.second;
                        const int dr[4] = {1,-1,0,0};
                        const int dc[4] = {0,0,1,-1};
                        for (int d = 0; d < 4; d++) {
                            int nx = x + dr[d], ny = y + dc[d];
                            if (nx >= 0 && nx < H && ny >= 0 && ny < W && grid[nx][ny]=='.') {
                                cand.emplace_back(nx, ny);
                            }
                        }
                    }
                    if (cand.empty()) break;
                    auto chosen = rnd.any(cand);
                    shape.push_back(chosen);
                    grid[chosen.first][chosen.second] = '?';
                }
                // assign letter
                char ch = char('a' + letterIdx);
                for (auto &p : shape) {
                    grid[p.first][p.second] = ch;
                }
                letterIdx++;
            }
        }
        // ensure at least one shape
        if (letterIdx == 0) {
            auto p0 = empties[0];
            int r0 = p0.first, c0 = p0.second;
            grid[r0][c0] = 'a';
        }
        // output this test case
        println(H, W);
        for (int i = 0; i < H; i++) {
            printf("%s\n", grid[i].c_str());
        }
    }
    return 0;
}
