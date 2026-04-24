#include "testlib.h"
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Shape hyper-parameter: wide, tall, or square
    string shape = rnd.next("wide|tall|square");
    int H, W;
    if (shape == "wide") {
        H = rnd.next(1, 3);
        W = rnd.next(5, 10);
    } else if (shape == "tall") {
        H = rnd.next(5, 10);
        W = rnd.next(1, 3);
    } else {
        H = rnd.next(1, 10);
        W = rnd.next(1, 10);
    }

    // Horse moves budget
    int K = rnd.next(0, 30);

    // Total cells and obstacle count hyper-parameter
    int cells = H * W;
    int t = rnd.next(-1, 1); // for wnext skew
    int maxHi = max(1, cells - 1);
    int M = rnd.wnext(maxHi, t);
    // Reserve start (0,0) and end (H-1,W-1)
    M = min(M, cells - 2);
    M = max(M, 0);

    // Prepare all positions except start and end
    vector<int> idx;
    for (int i = 0; i < cells; i++) {
        if (i == 0 || i == cells - 1) continue;
        idx.push_back(i);
    }
    shuffle(idx.begin(), idx.end());

    // Build grid and place obstacles
    vector<vector<int>> grid(H, vector<int>(W, 0));
    for (int i = 0; i < M; i++) {
        int pos = idx[i];
        int r = pos / W, c = pos % W;
        grid[r][c] = 1;
    }

    // Output
    println(K);
    println(W, H);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            printf("%d", grid[i][j]);
            if (j + 1 < W) printf(" ");
        }
        printf("\n");
    }

    return 0;
}
