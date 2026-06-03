#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Cell {
    char kind;
    int count;
};

int boundedValue(int mode) {
    if (mode == 0) return rnd.next(1, 9);
    if (mode == 1) return rnd.next(90, 99);
    if (mode == 2) return rnd.any(vector<int>{1, 2, 3, 97, 98, 99});
    return rnd.next(1, 99);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int r, c;

    if (mode == 0) {
        r = rnd.next(2, 4);
        c = rnd.next(2, 4);
    } else if (mode == 1) {
        r = rnd.next(2, 3);
        c = rnd.next(8, 18);
    } else if (mode == 2) {
        r = rnd.next(8, 18);
        c = rnd.next(2, 3);
    } else {
        r = rnd.next(3, 12);
        c = rnd.next(3, 12);
    }

    int valueMode = rnd.next(0, 3);
    int aBias = rnd.next(20, 80);
    vector<vector<Cell>> grid(r, vector<Cell>(c));

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            char kind = 'A';
            if (mode == 3) {
                kind = (i + j + rnd.next(0, 2) == 1 ? 'A' : 'B');
            } else if (mode == 4) {
                kind = (i * c < j * r ? 'A' : 'B');
                if (rnd.next(100) < 15) kind = (kind == 'A' ? 'B' : 'A');
            } else if (mode == 5) {
                kind = (j == 0 || i + 1 == r ? 'A' : 'B');
                if (rnd.next(100) < 20) kind = (kind == 'A' ? 'B' : 'A');
            } else {
                kind = (rnd.next(100) < aBias ? 'A' : 'B');
            }

            int count = boundedValue(valueMode);
            if (mode == 6 && ((i == 0 && j + 1 == c) || (i + 1 == r && j == 0))) {
                count = rnd.next(95, 99);
            }
            grid[i][j] = {kind, count};
        }
    }

    println(r, c);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (j > 0) printf(" ");
            printf("%c%d", grid[i][j].kind, grid[i][j].count);
        }
        printf("\n");
    }

    return 0;
}
