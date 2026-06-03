#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(0, 3) == 0 ? 3 : 5;
    int mode = rnd.next(0, 5);
    string ops = "+-*";
    vector<vector<string>> grid(n, vector<string>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if ((i + j) % 2 == 0) {
                int value;
                if (mode == 0) {
                    value = rnd.next(0, 5);
                } else if (mode == 1) {
                    value = rnd.next(0, 1) == 0 ? 0 : rnd.next(4, 5);
                } else if (mode == 2) {
                    value = rnd.next(0, 2);
                } else if (mode == 3) {
                    value = rnd.next(3, 5);
                } else {
                    value = (i == j || i + j == n - 1) ? rnd.next(0, 5) : rnd.next(1, 4);
                }
                grid[i][j] = to_string(value);
            } else {
                char op;
                if (mode == 0) {
                    op = rnd.any(ops);
                } else if (mode == 1) {
                    op = rnd.next(0, 2) == 0 ? '*' : '-';
                } else if (mode == 2) {
                    op = rnd.next(0, 3) == 0 ? '*' : '+';
                } else if (mode == 3) {
                    op = rnd.next(0, 2) == 0 ? '-' : '+';
                } else {
                    op = ops[(i + 2 * j + rnd.next(0, 2)) % 3];
                }
                grid[i][j] = string(1, op);
            }
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(grid[i]);
    }

    return 0;
}
