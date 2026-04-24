#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Initialize a 10x10 paper with zeros
    int a[10][10] = {};

    // Choose a base pattern type for diversity
    int type = rnd.next(0, 3);

    if (type == 0) {
        // Clustered rectangles
        int k = rnd.next(1, 4);  // number of clusters
        for (int t = 0; t < k; ++t) {
            int h = rnd.next(1, 4), w = rnd.next(1, 4);
            int r = rnd.next(0, 10 - h), c = rnd.next(0, 10 - w);
            for (int i = r; i < r + h; ++i) 
                for (int j = c; j < c + w; ++j) 
                    a[i][j] = 1;
        }
    } else if (type == 1) {
        // Stripes (horizontal or vertical)
        int stripes = rnd.next(1, 3);
        int orient = rnd.next(0, 1);
        for (int t = 0; t < stripes; ++t) {
            if (orient == 0) {
                int row = rnd.next(0, 9);
                int len = rnd.next(3, 10), c0 = rnd.next(0, 10 - len);
                for (int j = c0; j < c0 + len; ++j) 
                    a[row][j] = 1;
            } else {
                int col = rnd.next(0, 9);
                int len = rnd.next(3, 10), r0 = rnd.next(0, 10 - len);
                for (int i = r0; i < r0 + len; ++i) 
                    a[i][col] = 1;
            }
        }
    } else if (type == 2) {
        // One big block
        int bs = rnd.next(2, 6);
        int r0 = rnd.next(0, 10 - bs), c0 = rnd.next(0, 10 - bs);
        for (int i = r0; i < r0 + bs; ++i) 
            for (int j = c0; j < c0 + bs; ++j) 
                a[i][j] = 1;
    } else {
        // Random isolated ones
        int cnt = rnd.next(1, 20);
        vector<pair<int,int>> pos;
        for (int i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j)
                pos.emplace_back(i, j);
        shuffle(pos.begin(), pos.end());
        for (int t = 0; t < cnt && t < (int)pos.size(); ++t) {
            auto p = pos[t];
            a[p.first][p.second] = 1;
        }
    }

    // Add a small amount of noise
    double noiseP = rnd.next(0.0, 0.05);
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            if (rnd.next() < noiseP)
                a[i][j] = 1;

    // Output the 10x10 grid
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            printf("%d", a[i][j]);
            if (j < 9) printf(" ");
        }
        printf("\n");
    }

    return 0;
}
