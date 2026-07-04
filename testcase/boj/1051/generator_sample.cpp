#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;

    if (mode == 4) {
        if (rnd.next(0, 1) == 0) {
            n = 1;
            m = rnd.next(1, 50);
        } else {
            n = rnd.next(1, 50);
            m = 1;
        }
    } else if (mode == 5) {
        n = rnd.next(15, 50);
        m = rnd.next(15, 50);
    } else {
        n = rnd.next(1, 12);
        m = rnd.next(1, 12);
    }

    int maxDigit = rnd.next(1, 9);
    vector<string> grid(n, string(m, '0'));

    if (mode == 0) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = char('0' + rnd.next(0, maxDigit));
    } else if (mode == 1) {
        char digit = char('0' + rnd.next(0, 9));
        for (int i = 0; i < n; ++i)
            grid[i].assign(m, digit);
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = char('0' + ((i + j) % 2));
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = char('0' + ((i * 3 + j * 5 + rnd.next(0, 1)) % 10));

        int side = rnd.next(1, min(n, m));
        int top = rnd.next(0, n - side);
        int left = rnd.next(0, m - side);
        char digit = char('0' + rnd.next(0, 9));
        grid[top][left] = digit;
        grid[top + side - 1][left] = digit;
        grid[top][left + side - 1] = digit;
        grid[top + side - 1][left + side - 1] = digit;
    } else {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = char('0' + rnd.next(0, 9));
    }

    println(n, m);
    for (const string& row : grid)
        println(row);

    return 0;
}
