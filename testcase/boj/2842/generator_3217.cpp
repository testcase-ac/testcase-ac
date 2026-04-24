#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small size
    int N = rnd.next(2, 10);
    // Prepare map
    vector<string> grid(N, string(N, '.'));
    int px = rnd.next(0, N-1), py = rnd.next(0, N-1);
    grid[px][py] = 'P';
    int mapType = rnd.next(0, 2);
    vector<pair<int,int>> cells;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (!(i == px && j == py))
                cells.emplace_back(i, j);
    if (mapType == 0) {
        double house_prob = 0.1 + rnd.next() * 0.5; // [0.1,0.6]
        for (auto &c : cells)
            if (rnd.next() < house_prob)
                grid[c.first][c.second] = 'K';
    } else if (mapType == 1) {
        double base = 0.4 + rnd.next() * 0.4; // [0.4,0.8]
        for (auto &c : cells) {
            int dx = abs(c.first - px), dy = abs(c.second - py);
            int dist = max(dx, dy);
            double prob = max(0.05, base - double(dist) / double(N));
            if (rnd.next() < prob)
                grid[c.first][c.second] = 'K';
        }
    } else {
        double borderp = 0.4 + rnd.next() * 0.4;
        double innerp = max(0.05, 0.1 + rnd.next() * 0.2);
        for (auto &c : cells) {
            int i = c.first, j = c.second;
            double p = (i==0||j==0||i==N-1||j==N-1 ? borderp : innerp);
            if (rnd.next() < p)
                grid[i][j] = 'K';
        }
    }
    // Ensure at least one K
    bool hasK = false;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (grid[i][j] == 'K') hasK = true;
    if (!hasK) {
        auto c = rnd.any(cells);
        grid[c.first][c.second] = 'K';
    }
    // Heights hyper-parameters
    int minH = rnd.next(1, 100);
    int maxH = rnd.next(minH, minH + rnd.next(0, 100));
    int hType = rnd.next(0, 2);

    // Output
    printf("%d\n", N);
    for (int i = 0; i < N; i++)
        printf("%s\n", grid[i].c_str());
    for (int i = 0; i < N; i++) {
        vector<int> row(N);
        for (int j = 0; j < N; j++) {
            if (hType == 0) {
                row[j] = rnd.next(minH, maxH);
            } else if (hType == 1) {
                double ratio = (N == 1 ? 0.0 : double(i) / double(N - 1));
                int baseH = minH + int(round(ratio * (maxH - minH)));
                int noiseR = max(1, (maxH - minH) / (2 * N));
                row[j] = min(maxH, baseH + rnd.next(0, noiseR));
            } else {
                double ratio = (N == 1 ? 0.0 : double(i + j) / double(2 * (N - 1)));
                int baseH = minH + int(round(ratio * (maxH - minH)));
                int noiseR = max(1, (maxH - minH) / (2 * N));
                row[j] = min(maxH, baseH + rnd.next(0, noiseR));
            }
        }
        println(row);
    }
    return 0;
}
