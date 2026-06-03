#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 4);
    int m = rnd.next(1, 4);
    int mode = rnd.next(0, 5);
    vector<string> grid(n, string(m, '0'));

    if (mode == 0) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = char('0' + rnd.next(0, 9));
    } else if (mode == 1) {
        char digit = char('0' + rnd.next(0, 9));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = digit;
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = rnd.next(0, 3) == 0 ? char('0' + rnd.next(1, 9)) : '0';
    } else if (mode == 3) {
        int start = rnd.next(0, 9);
        int step = rnd.next(1, 9);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = char('0' + (start + step * (i * m + j)) % 10);
    } else if (mode == 4) {
        char a = char('0' + rnd.next(0, 9));
        char b = char('0' + rnd.next(0, 9));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = ((i + j) % 2 == 0) ? a : b;
    } else {
        for (int i = 0; i < n; ++i) {
            char digit = char('0' + rnd.next(0, 9));
            for (int j = 0; j < m; ++j)
                grid[i][j] = digit;
        }
    }

    println(n, m);
    for (const string& row : grid)
        println(row);

    return 0;
}
