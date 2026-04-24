#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Dimensions
    int R = rnd.next(3, 15);
    int C = rnd.next(3, 15);

    // Initialize empty grid
    vector<string> grid(R, string(C, '.'));

    // Determine number of enclosures
    int maxE = (R * C) / 9;
    if (maxE < 1) maxE = 1;
    maxE = min(maxE, 4);
    int E = rnd.next(1, maxE);

    struct Rect { int r0, c0, h, w; };
    vector<Rect> rects;
    int tries = E * 10;

    // Place E non-overlapping rectangular fences
    while (tries-- > 0 && (int)rects.size() < E) {
        // Height and width hyper-parameter: sometimes small, sometimes large
        int ht = rnd.wnext(R, rnd.next(-1, 1));
        int wd = rnd.wnext(C, rnd.next(-1, 1));
        int h = max(3, min(ht, R));
        int w = max(3, min(wd, C));
        int r0 = rnd.next(0, R - h);
        int c0 = rnd.next(0, C - w);
        int r1 = r0 + h - 1;
        int c1 = c0 + w - 1;

        // Check if fence border cells are free
        bool ok = true;
        for (int j = c0; j <= c1 && ok; j++) {
            if (grid[r0][j] == '#' || grid[r1][j] == '#') ok = false;
        }
        for (int i = r0; i <= r1 && ok; i++) {
            if (grid[i][c0] == '#' || grid[i][c1] == '#') ok = false;
        }
        if (!ok) continue;

        // Draw fences
        for (int j = c0; j <= c1; j++) {
            grid[r0][j] = '#';
            grid[r1][j] = '#';
        }
        for (int i = r0; i <= r1; i++) {
            grid[i][c0] = '#';
            grid[i][c1] = '#';
        }
        rects.push_back({r0, c0, h, w});
    }

    // Fill each enclosure interior with sheep('k'), wolves('v'), or empty
    for (auto &rc : rects) {
        double fillProb = rnd.next(0.0, 1.0);
        double sheepProb = rnd.next(0.0, 1.0);
        for (int i = rc.r0 + 1; i < rc.r0 + rc.h - 1; i++) {
            for (int j = rc.c0 + 1; j < rc.c0 + rc.w - 1; j++) {
                if (rnd.next() < fillProb) {
                    grid[i][j] = (rnd.next() < sheepProb ? 'k' : 'v');
                }
            }
        }
    }

    // Output
    printf("%d %d\n", R, C);
    for (int i = 0; i < R; i++) {
        printf("%s\n", grid[i].c_str());
    }
    return 0;
}
