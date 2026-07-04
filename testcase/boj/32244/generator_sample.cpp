#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int advanceState(int value, int delta) {
    return (value + delta - 1) % 4 + 1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> sizes = {2, 4, 6, 8, 10, 12};
    int n = rnd.any(sizes);
    int mode = rnd.next(0, 4);

    vector<string> initial(n, string(n, '1'));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            initial[i][j] = char('0' + rnd.next(1, 4));
        }
    }

    vector<string> target = initial;

    if (mode == 0) {
        // Leave target equal to initial.
    } else if (mode == 1) {
        int row = rnd.next(0, n - 1);
        int col = rnd.next(0, n - 1);
        int delta = rnd.next(1, 3);
        for (int j = 0; j < n; ++j) {
            target[row][j] = char('0' + advanceState(target[row][j] - '0', delta));
        }
        for (int i = 0; i < n; ++i) {
            if (i == row) continue;
            target[i][col] = char('0' + advanceState(target[i][col] - '0', delta));
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(0, 3);
            for (int j = 0; j < n; ++j) {
                target[i][j] = char('0' + advanceState(target[i][j] - '0', delta));
            }
        }
    } else if (mode == 3) {
        for (int j = 0; j < n; ++j) {
            int delta = rnd.next(0, 3);
            for (int i = 0; i < n; ++i) {
                target[i][j] = char('0' + advanceState(target[i][j] - '0', delta));
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                target[i][j] = char('0' + rnd.next(1, 4));
            }
        }
    }

    println(n);
    for (const string& row : initial) {
        println(row);
    }
    for (const string& row : target) {
        println(row);
    }

    return 0;
}
