#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 6) {
        n = rnd.next(12, 20);
    } else {
        n = rnd.next(4, 12);
    }

    vector<vector<int>> grid(n, vector<int>(n));

    if (mode == 0) {
        int value = rnd.next(3);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                grid[i][j] = rnd.next(4) == 0 ? rnd.next(3) : value;
    } else if (mode == 1) {
        int offset = rnd.next(3);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                grid[i][j] = (i + j + offset) % 3;
    } else if (mode == 2) {
        int goodRow = rnd.next(n);
        int goodCol = rnd.next(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == goodRow || j == goodCol) {
                    grid[i][j] = (i + j) % 3;
                } else {
                    grid[i][j] = rnd.next(1, 2);
                }
            }
        }
    } else if (mode == 3) {
        int rowShift = rnd.next(3);
        for (int i = 0; i < n; ++i) {
            int base = (i + rowShift) % 3;
            for (int j = 0; j < n; ++j)
                grid[i][j] = rnd.next(3) == 0 ? rnd.next(3) : base;
        }
    } else if (mode == 4) {
        int colShift = rnd.next(3);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int base = (j + colShift) % 3;
                grid[i][j] = rnd.next(3) == 0 ? rnd.next(3) : base;
            }
        }
    } else if (mode == 5) {
        int block = rnd.next(2, 4);
        int offset = rnd.next(3);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                grid[i][j] = ((i / block) + (j / block) + offset) % 3;
    } else {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                grid[i][j] = rnd.next(3);
    }

    println(n);
    for (int i = 0; i < n; ++i)
        println(grid[i]);

    return 0;
}
