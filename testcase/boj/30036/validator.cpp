#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // I, N, K
    int I = inf.readInt(1, 100, "I");
    inf.readSpace();
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int K = inf.readInt(1, 100, "K");
    inf.readEoln();

    // Ink string: length I, uppercase letters
    string ink = inf.readToken("[A-Z]{1,100}", "ink");
    inf.readEoln();
    ensuref((int)ink.size() == I,
            "Ink string length (%d) must equal I (%d)", (int)ink.size(), I);

    // Stage grid: N lines of length N, chars '.', '#', '@'
    vector<string> grid(N);
    int startY = -1, startX = -1;
    int atCount = 0;

    for (int y = 0; y < N; ++y) {
        grid[y] = inf.readToken("[@.#]{1,100}", "grid_row");
        inf.readEoln();
        ensuref((int)grid[y].size() == N,
                "Row %d length (%d) must equal N (%d)", y + 1, (int)grid[y].size(), N);
        for (int x = 0; x < N; ++x) {
            if (grid[y][x] == '@') {
                ++atCount;
                startY = y;
                startX = x;
            }
        }
    }
    ensuref(atCount == 1, "There must be exactly one '@' in the grid, found %d", atCount);

    // Commands: one line, length K, chars UDLRjJ
    string cmd = inf.readToken("[A-Za-z]{1,100}", "commands");
    inf.readEoln();
    ensuref((int)cmd.size() == K,
            "Command string length (%d) must equal K (%d)", (int)cmd.size(), K);
    for (int i = 0; i < K; ++i) {
        char c = cmd[i];
        ensuref(c == 'U' || c == 'D' || c == 'L' || c == 'R' || c == 'j' || c == 'J',
                "Invalid command character '%c' at position %d", c, i + 1);
    }

    // --- Global property checks via simulation ---

    // We must ensure that all commands are valid according to movement / ink rules
    // and no out-of-bounds / obstacle overlap ever occurs (movement commands
    // are ignored in such cases), and that jumps and coloring behave as specified.

    int y = startY, x = startX;
    int inkAmt = 0;
    int jumpCount = 0;
    vector<string> colorGrid = grid; // will hold final colored obstacles

    auto inBounds = [&](int yy, int xx) {
        return 0 <= yy && yy < N && 0 <= xx && xx < N;
    };

    for (int i = 0; i < K; ++i) {
        char c = cmd[i];
        if (c == 'j') {
            // Ink charging
            inkAmt++;
            continue;
        }
        if (c == 'J') {
            // Jump & ink spread
            jumpCount++;
            char col = ink[(jumpCount - 1) % I]; // 0-based
            int m = inkAmt;
            if (m > 0) {
                // Spread ink over Manhattan distance <= m, only to obstacles (# or A-Z)
                // We use a safe simulation: check bounds, but we don't need extra
                // properties beyond problem statement.
                for (int yy = max(0, y - m); yy <= min(N - 1, y + m); ++yy) {
                    int rem = m - abs(yy - y);
                    int xl = max(0, x - rem);
                    int xr = min(N - 1, x + rem);
                    for (int xx = xl; xx <= xr; ++xx) {
                        if (grid[yy][xx] == '#' || (colorGrid[yy][xx] >= 'A' && colorGrid[yy][xx] <= 'Z')) {
                            colorGrid[yy][xx] = col;
                        }
                    }
                }
            }
            inkAmt = 0;
            continue;
        }
        // Movement commands
        int ny = y, nx = x;
        if (c == 'U') ny--;
        else if (c == 'D') ny++;
        else if (c == 'L') nx--;
        else if (c == 'R') nx++;

        if (!inBounds(ny, nx)) {
            // Command ignored
            continue;
        }
        char dest = colorGrid[ny][nx];
        // Obstacles: original '#', or colored uppercase that originated from '#'.
        // But note: '@' can only be on empty or previous '@'; grid guarantees only one '@'.
        if (dest == '#' || (dest >= 'A' && dest <= 'Z')) {
            // Cannot move into obstacle; ignore
            continue;
        }
        // Move the player
        y = ny;
        x = nx;
    }

    // No extra guarantees in statement (like answer always exists) to check beyond this.

    inf.readEof();
}
