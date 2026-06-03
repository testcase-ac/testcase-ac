#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int m = rnd.next(1, 10);
    int n = rnd.next(1, 10);
    vector<int> border(4);

    if (mode == 0) {
        m = rnd.next(1, 3);
        n = rnd.next(1, 3);
        fill(border.begin(), border.end(), 0);
    } else if (mode == 1) {
        m = 10;
        n = 10;
        fill(border.begin(), border.end(), 5);
    } else if (mode == 2) {
        m = rnd.next(1, 10);
        n = rnd.next(1, 10);
        border = {rnd.next(0, 5), 0, rnd.next(0, 5), 0};
    } else if (mode == 3) {
        m = rnd.next(1, 10);
        n = rnd.next(1, 10);
        border = {0, rnd.next(0, 5), 0, rnd.next(0, 5)};
    } else {
        for (int& value : border) {
            value = rnd.next(0, 5);
        }
    }

    if (mode != 0 && mode != 1 && mode != 2 && mode != 3) {
        if (rnd.next(0, 3) == 0) {
            border[rnd.next(0, 3)] = rnd.next(0, 1) ? 0 : 5;
        }
    }

    vector<string> rows;
    int pattern = rnd.next(0, 4);
    char base = char('a' + rnd.next(0, 25));
    for (int i = 0; i < m; ++i) {
        string row;
        for (int j = 0; j < n; ++j) {
            char c;
            if (pattern == 0) {
                c = base;
            } else if (pattern == 1) {
                c = char('a' + (i + j + base - 'a') % 26);
            } else if (pattern == 2) {
                c = char('a' + (i * n + j + base - 'a') % 26);
            } else {
                c = char('a' + rnd.next(0, 25));
            }
            row += c;
        }
        rows.push_back(row);
    }

    println(m, n);
    println(border);
    for (const string& row : rows) {
        println(row);
    }

    return 0;
}
