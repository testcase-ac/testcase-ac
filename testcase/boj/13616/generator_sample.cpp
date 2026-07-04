#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

char randomLetterFrom(const string& alphabet) {
    return alphabet[rnd.next((int)alphabet.size())];
}

char flipCase(char c) {
    if ('a' <= c && c <= 'j') return char(c - 'a' + 'A');
    return char(c - 'A' + 'a');
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 4);
    } else if (mode == 4) {
        n = rnd.next(20, 30);
    } else {
        n = rnd.next(5, 12);
    }

    vector<string> grid(n, string(n, 'a'));

    if (mode == 0) {
        string alphabet = "abAB";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = randomLetterFrom(alphabet);
            }
        }
    } else if (mode == 1) {
        string alphabet = "abcde";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = randomLetterFrom(alphabet);
            }
        }
        for (int i = 0; i < n; ++i) {
            grid[i][0] = char('a' + rnd.next(5));
        }
        for (int j = 0; j < n; ++j) {
            grid[n - 1][j] = char('a' + rnd.next(5));
        }
    } else if (mode == 2) {
        char base = char('a' + rnd.next(10));
        char wall = flipCase(base);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = base;
            }
        }
        int split = rnd.next(1, n - 2);
        for (int i = 0; i < n; ++i) {
            grid[i][split] = wall;
        }
        int gap = rnd.next(n);
        grid[gap][split] = base;
        grid[0][0] = base;
        grid[n - 1][n - 1] = base;
    } else if (mode == 3) {
        string alphabet = "abcABCdefDEF";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = randomLetterFrom(alphabet);
            }
        }
        for (int i = 0; i < n; ++i) {
            int j = i;
            char c = char('a' + (i % 3));
            grid[i][j] = (rnd.next(2) == 0 ? c : flipCase(c));
            if (j + 1 < n && rnd.next(3) == 0) {
                grid[i][j + 1] = flipCase(grid[i][j]);
            }
        }
    } else {
        string alphabet = "abcdefghijABCDEFGHIJ";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (rnd.next(100) < 70) {
                    grid[i][j] = char('a' + rnd.next(4));
                } else {
                    grid[i][j] = randomLetterFrom(alphabet);
                }
            }
        }
    }

    println(n);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
