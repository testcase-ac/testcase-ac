#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // Directions: U, D, L, R
    // U: (-1,0), D: (+1,0), L: (0,-1), R: (0,+1)
    int dx[256], dy[256];
    for (int i = 0; i < 256; ++i) dx[i] = dy[i] = 0;
    dx['U'] = -1; dy['U'] = 0;
    dx['D'] = 1;  dy['D'] = 0;
    dx['L'] = 0;  dy['L'] = -1;
    dx['R'] = 0;  dy['R'] = 1;

    vector<string> grid(N);
    for (int i = 0; i < N; ++i) {
        // Read line with exactly M characters, only UDLR allowed
        grid[i] = inf.readLine("[UDLR]{"+to_string(M)+","+to_string(M)+"}", "row");
        ensuref((int)grid[i].size() == M, "Row %d length is not M (%d != %d)", i+1, (int)grid[i].size(), M);
        for (int j = 0; j < M; ++j) {
            char c = grid[i][j];
            ensuref(c == 'U' || c == 'D' || c == 'L' || c == 'R',
                "Invalid character '%c' at row %d, col %d", c, i+1, j+1);
            int ni = i + dx[(unsigned char)c];
            int nj = j + dy[(unsigned char)c];
            ensuref(0 <= ni && ni < N && 0 <= nj && nj < M,
                "Cell (%d,%d) with direction '%c' goes out of bounds to (%d,%d)", i+1, j+1, c, ni+1, nj+1);
        }
    }

    inf.readEof();
}
