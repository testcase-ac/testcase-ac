#include "testlib.h"
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for dimensions
    int R = rnd.next(2, 10);
    int C = rnd.next(2, 10);

    int tot = R * C;
    // Bias for number of blocks: t >0 => more blocks, t<0 => fewer
    vector<int> blockBiases = {-2, -1, 0, 1, 2};
    int tBias = rnd.any(blockBiases);
    // Number of blocked cells
    int blkCount = rnd.wnext(tot, tBias);
    // Leave at least 2 cells free for a valid word
    blkCount = min(blkCount, tot - 2);

    // Prepare all cell indices
    vector<int> cells(tot);
    iota(cells.begin(), cells.end(), 0);
    shuffle(cells.begin(), cells.end());

    // Fill flat grid with random letters
    vector<char> flat(tot);
    for (int i = 0; i < tot; i++) {
        flat[i] = char('a' + rnd.next(0, 25));
    }
    // Place blocks
    for (int i = 0; i < blkCount; i++) {
        flat[cells[i]] = '#';
    }

    // Ensure at least one word segment of length >= 2
    bool horiz = rnd.next(0, 1) == 0;
    int maxL = horiz ? C : R;
    vector<int> lenBiases = {-1, 0, 1};
    int tBias2 = rnd.any(lenBiases);
    int segLen;
    if (maxL <= 2) {
        segLen = 2;
    } else {
        segLen = rnd.wnext(maxL - 2, tBias2) + 2;
    }
    int r0, c0;
    if (horiz) {
        r0 = rnd.next(0, R - 1);
        c0 = rnd.next(0, C - segLen);
    } else {
        r0 = rnd.next(0, R - segLen);
        c0 = rnd.next(0, C - 1);
    }
    // Override that segment to letters
    for (int k = 0; k < segLen; k++) {
        int idx = horiz ? (r0 * C + (c0 + k)) : ((r0 + k) * C + c0);
        flat[idx] = char('a' + rnd.next(0, 25));
    }

    // Build 2D grid
    vector<string> grid(R, string(C, '#'));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            grid[i][j] = flat[i * C + j];
        }
    }

    // Output
    println(R, C);
    for (auto &row : grid)
        println(row);

    return 0;
}
