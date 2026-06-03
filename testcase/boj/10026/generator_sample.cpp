#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode <= 4) {
        n = rnd.next(5, 14);
    } else {
        n = rnd.next(15, 25);
    }

    vector<string> grid(n, string(n, 'R'));
    string colors = "RGB";

    if (mode == 0) {
        char color = rnd.any(colors);
        for (int r = 0; r < n; ++r)
            for (int c = 0; c < n; ++c)
                grid[r][c] = color;
    } else if (mode == 1) {
        for (int r = 0; r < n; ++r) {
            char color = rnd.any(colors);
            for (int c = 0; c < n; ++c) grid[r][c] = color;
        }
    } else if (mode == 2) {
        for (int c = 0; c < n; ++c) {
            char color = rnd.any(colors);
            for (int r = 0; r < n; ++r) grid[r][c] = color;
        }
    } else if (mode == 3) {
        for (int r = 0; r < n; ++r)
            for (int c = 0; c < n; ++c)
                grid[r][c] = ((r + c + rnd.next(0, 1)) % 2 == 0) ? 'B' : rnd.any(string("RG"));
    } else if (mode == 4) {
        int block = rnd.next(2, 4);
        for (int r = 0; r < n; ++r)
            for (int c = 0; c < n; ++c)
                grid[r][c] = colors[((r / block) + (c / block) + rnd.next(0, 2)) % 3];
    } else if (mode == 5) {
        string palette = rnd.next(0, 1) ? "RG" : "RGB";
        for (int r = 0; r < n; ++r)
            for (int c = 0; c < n; ++c)
                grid[r][c] = rnd.any(palette);
    } else {
        for (int r = 0; r < n; ++r)
            for (int c = 0; c < n; ++c)
                grid[r][c] = colors[(r * 2 + c + rnd.next(0, 2)) % 3];
    }

    println(n);
    for (const string& row : grid) println(row);

    return 0;
}
