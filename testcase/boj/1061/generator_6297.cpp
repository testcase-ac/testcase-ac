#include "testlib.h"
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Dimensions
    int N = rnd.next(1, 15);
    int M = rnd.next(1, 15);

    // Pattern choices
    vector<string> patterns = {"uniform", "random", "stripes", "checker", "blocks", "diagonal"};
    string pat = rnd.any(patterns);
    string colors = "RGB";

    vector<string> grid(N, string(M, 'R'));

    if (pat == "uniform") {
        // All one color
        char c = rnd.any(colors);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                grid[i][j] = c;
    }
    else if (pat == "random") {
        // Completely random
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                grid[i][j] = rnd.any(colors);
    }
    else if (pat == "stripes") {
        // Horizontal stripes of height hs
        int hs = rnd.next(1, max(1, N));
        for (int i = 0; i < N; i++) {
            char c = colors[(i/hs) % 3];
            for (int j = 0; j < M; j++)
                grid[i][j] = c;
        }
    }
    else if (pat == "checker") {
        // 3-color checkerboard (by sum mod 3)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                grid[i][j] = colors[(i + j) % 3];
    }
    else if (pat == "blocks" && N > 1 && M > 1) {
        // 2x2 blocks split
        int splitR = rnd.next(1, N - 1);
        int splitC = rnd.next(1, M - 1);
        char blockColor[4];
        for (int b = 0; b < 4; b++)
            blockColor[b] = rnd.any(colors);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                int bi = i < splitR ? 0 : 1;
                int bj = j < splitC ? 0 : 1;
                int id = bi * 2 + bj;
                grid[i][j] = blockColor[id];
            }
        }
    }
    else {
        // Diagonal-based pattern
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++) {
                if (i == j) grid[i][j] = 'R';
                else if ((i + j) % 2 == 0) grid[i][j] = 'G';
                else grid[i][j] = 'B';
            }
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; i++)
        printf("%s\n", grid[i].c_str());

    return 0;
}
