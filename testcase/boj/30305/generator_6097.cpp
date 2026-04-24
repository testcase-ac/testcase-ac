#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for dimension variability: small or medium
    int h = rnd.next(0,1) ? rnd.next(1,5) : rnd.next(6,10);
    int w = rnd.next(0,1) ? rnd.next(1,5) : rnd.next(6,10);
    vector<string> grid(h, string(w, '.'));
    // Choose shape type: 0 = cross, 1 = perimeter, 2 = full rectangle
    int shapeType = rnd.next(0,2);
    if (shapeType == 2) {
        // Full rectangle
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
                grid[i][j] = '#';
    } else if (shapeType == 0) {
        // Cross shape: full row and full column
        int rr = rnd.next(1, h) - 1;
        int cc = rnd.next(1, w) - 1;
        for (int j = 0; j < w; j++) grid[rr][j] = '#';
        for (int i = 0; i < h; i++) grid[i][cc] = '#';
    } else {
        // Perimeter shape if possible, else fallback to cross
        if (h >= 2 && w >= 2) {
            // Top row
            for (int j = 0; j < w; j++) grid[0][j] = '#';
            // Right column (excluding top)
            for (int i = 1; i < h; i++) grid[i][w-1] = '#';
            // Bottom row (excluding bottom-right)
            for (int j = w-2; j >= 0; j--) grid[h-1][j] = '#';
            // Left column (excluding corners)
            for (int i = h-2; i >= 1; i--) grid[i][0] = '#';
        } else {
            // Fallback to cross if perimeter not feasible
            int rr = rnd.next(1, h) - 1;
            int cc = rnd.next(1, w) - 1;
            for (int j = 0; j < w; j++) grid[rr][j] = '#';
            for (int i = 0; i < h; i++) grid[i][cc] = '#';
        }
    }
    // Output block
    println(h, w);
    for (int i = 0; i < h; i++)
        println(grid[i]);
    return 0;
}
