#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small dimensions H, W with H*W <= 20
    int H, W;
    do {
        H = rnd.next(1, 5);
        W = rnd.next(1, 10);
    } while ((long long)H * W > 20);

    int HW = H * W;
    // Choose N in [1, HW], may or may not admit a valid rectangle (to test -1 cases)
    int N = rnd.next(1, HW);

    // Generate sweetness values with a few patterns for diversity
    vector<int> cells(HW);
    // With small chance, make all values equal
    if (rnd.next(0, 4) == 0) {
        int v = rnd.next(1, 100);
        for (int &x : cells) x = v;
    } else {
        // Otherwise mix uniform and weighted sampling for varied distributions
        int t = rnd.next(-2, 2);
        for (int i = 0; i < HW; i++) {
            if (rnd.next(0, 1) == 0) {
                // weighted extremes or central
                cells[i] = rnd.wnext(100, t) + 1;
            } else {
                // plain uniform
                cells[i] = rnd.next(1, 100);
            }
        }
    }
    // Shuffle the cell values so patterns are not row-aligned
    shuffle(cells.begin(), cells.end());

    // Output
    println(H, W, N);
    for (int i = 0; i < H; i++) {
        vector<int> row;
        for (int j = 0; j < W; j++) {
            row.push_back(cells[i * W + j]);
        }
        println(row);
    }
    return 0;
}
