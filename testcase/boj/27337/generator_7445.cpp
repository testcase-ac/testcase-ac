#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Dimensions small for manual verification
    int H = rnd.next(1, 15);
    int W = rnd.next(1, 15);
    // Number of distinct colors
    int C = rnd.next(1, 5);
    // Choose a pattern for variability
    int pattern = rnd.next(0, 3);

    vector<vector<int>> A(H, vector<int>(W, 1));
    if (pattern == 0) {
        // Completely random noise
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                A[i][j] = rnd.next(1, C);
    } else if (pattern == 1) {
        // Horizontal stripes
        for (int i = 0; i < H; i++) {
            int color = rnd.next(1, C);
            for (int j = 0; j < W; j++)
                A[i][j] = color;
        }
    } else if (pattern == 2) {
        // Vertical stripes
        for (int j = 0; j < W; j++) {
            int color = rnd.next(1, C);
            for (int i = 0; i < H; i++)
                A[i][j] = color;
        }
    } else {
        // Clustered regions via Voronoi
        int maxSeeds = min(5, H * W);
        int B = rnd.next(1, maxSeeds);
        vector<pair<int,int>> seeds;
        vector<int> seedColor;
        for (int b = 0; b < B; b++) {
            int si = rnd.next(0, H-1);
            int sj = rnd.next(0, W-1);
            seeds.emplace_back(si, sj);
            seedColor.push_back(rnd.next(1, C));
        }
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                int best = 0, bd = abs(i - seeds[0].first) + abs(j - seeds[0].second);
                for (int b = 1; b < B; b++) {
                    int d = abs(i - seeds[b].first) + abs(j - seeds[b].second);
                    if (d < bd) {
                        bd = d;
                        best = b;
                    }
                }
                A[i][j] = seedColor[best];
            }
        }
    }

    // Output the generated test case
    println(H, W);
    for (int i = 0; i < H; i++) {
        println(A[i]);
    }
    return 0;
}
