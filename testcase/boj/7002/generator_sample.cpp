#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

static string makeRow(int m, int mode) {
    string row;
    row.reserve(m);
    for (int col = 0; col < m; ++col) {
        if (mode == 0) {
            row.push_back(rnd.next(4) == 0 ? 'O' : '*');
        } else if (mode == 1) {
            row.push_back(rnd.next(5) == 0 ? 'X' : (rnd.next(3) == 0 ? 'O' : '*'));
        } else if (mode == 2) {
            row.push_back((col % 2 == 0) ? 'O' : '*');
        } else {
            int pick = rnd.next(10);
            row.push_back(pick < 2 ? 'X' : (pick < 5 ? 'O' : '*'));
        }
    }
    return row;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tc = rnd.next(1, 8);
    println(tc);

    for (int caseNo = 0; caseNo < tc; ++caseNo) {
        int shape = rnd.next(4);
        int n = 1, m = 1;
        if (shape == 0) {
            n = rnd.next(1, 4);
            m = rnd.next(1, 5);
        } else if (shape == 1) {
            n = rnd.next(5, 10);
            m = rnd.next(1, 3);
        } else if (shape == 2) {
            n = rnd.next(1, 3);
            m = rnd.next(5, 10);
        } else {
            n = rnd.next(4, 8);
            m = rnd.next(4, 8);
        }

        int t = rnd.next(1, 20);
        if (rnd.next(6) == 0) {
            t = rnd.next(1000, 1000000);
        }

        int r = rnd.next(1, n + m + 3);
        if (rnd.next(6) == 0) {
            r = rnd.next(1000000, 100000000);
        }

        println(n, m, t, r);

        int mode = rnd.next(4);
        for (int row = 0; row < n; ++row) {
            string line = makeRow(m, mode);
            if (mode == 2 && row % 2 == 1) {
                for (char& cell : line) {
                    if (cell == 'O') {
                        cell = '*';
                    } else if (rnd.next(5) == 0) {
                        cell = 'X';
                    }
                }
            }
            println(line);
        }
    }

    return 0;
}
