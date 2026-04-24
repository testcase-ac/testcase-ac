#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Dimensions
    int H = rnd.next(1, 10);
    int W = rnd.next(1, 10);
    vector<string> grid(H, string(W, '.'));

    // Generate each row with a random pattern for diversity
    for (int i = 0; i < H; i++) {
        int pat = rnd.next(0, 2);
        if (pat == 0) {
            // Uniform random clouds with random density
            double p = rnd.next(0.0, 1.0);
            for (int j = 0; j < W; j++) {
                if (rnd.next() < p) grid[i][j] = 'c';
            }
        } else if (pat == 1) {
            // Several small clusters
            int maxClusters = max(1, W / 5);
            int clusters = rnd.next(1, maxClusters);
            for (int t = 0; t < clusters; t++) {
                int center = rnd.next(0, W - 1);
                int radius = rnd.next(0, 1);
                for (int d = 0; d <= radius; d++) {
                    if (center + d < W) grid[i][center + d] = 'c';
                    if (center - d >= 0) grid[i][center - d] = 'c';
                }
            }
        } else {
            // Prefix of clouds
            int prefixLen = rnd.next(0, W);
            for (int j = 0; j < prefixLen; j++) {
                grid[i][j] = 'c';
            }
            // Optional extra random clouds
            int extra = rnd.next(0, W / 3);
            vector<int> pos(W);
            iota(pos.begin(), pos.end(), 0);
            shuffle(pos.begin(), pos.end());
            for (int t = 0; t < extra; t++) {
                grid[i][pos[t]] = 'c';
            }
        }
    }

    // Output
    println(H, W);
    for (int i = 0; i < H; i++) {
        printf("%s\n", grid[i].c_str());
    }
    return 0;
}
