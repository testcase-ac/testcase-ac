#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int r, c;
    if (mode == 0) {
        r = 1;
        c = rnd.next(1, 12);
    } else if (mode == 1) {
        r = rnd.next(1, 12);
        c = 1;
    } else if (mode == 2) {
        r = rnd.next(2, 4);
        c = rnd.next(2, 4);
    } else if (mode == 3) {
        r = rnd.next(5, 10);
        c = rnd.next(5, 10);
    } else {
        r = rnd.next(2, 8);
        c = rnd.next(2, 12);
    }

    vector<string> grid(r, string(c, '0'));
    int base = rnd.next(0, 7);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            int dir;
            if (mode <= 1) {
                dir = rnd.next(0, 7);
            } else if (mode == 2) {
                dir = (base + i + j) % 8;
            } else if (mode == 3) {
                dir = rnd.next() < 0.70 ? base : rnd.next(0, 7);
            } else {
                dir = (i % 2 == 0) ? 2 : 6;
                if (rnd.next() < 0.25) dir = rnd.next(0, 7);
            }
            grid[i][j] = char('0' + dir);
        }
    }

    int n;
    if (rnd.next(0, 9) == 0) {
        n = 0;
    } else if (mode <= 1) {
        n = rnd.next(1, 8);
    } else {
        n = rnd.next(1, 20);
    }

    println(r, c);
    for (const string& row : grid) {
        println(row);
    }
    println(n);

    for (int q = 0; q < n; ++q) {
        int rs, cs, rd, cd;
        if (q == 0 && rnd.next(0, 3) == 0) {
            rs = rd = rnd.next(1, r);
            cs = cd = rnd.next(1, c);
        } else if (q == 1 && r > 1 && c > 1) {
            rs = 1;
            cs = 1;
            rd = r;
            cd = c;
        } else {
            rs = rnd.next(1, r);
            cs = rnd.next(1, c);
            rd = rnd.next(1, r);
            cd = rnd.next(1, c);
        }
        println(rs, cs, rd, cd);
    }

    return 0;
}
