#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string letters = "dbqp";
    int n;
    int sizeMode = rnd.next(4);
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode == 1) {
        n = rnd.next(2, 4);
    } else if (sizeMode == 2) {
        n = rnd.next(5, 7);
    } else {
        n = rnd.next(8, 10);
    }

    int d = rnd.next(1, 2);
    int pattern = rnd.next(5);
    vector<string> grid(n, string(n, 'd'));

    if (pattern == 0) {
        char c = rnd.any(letters);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = c;
            }
        }
    } else if (pattern == 1) {
        for (int i = 0; i < n; ++i) {
            char c = rnd.any(letters);
            for (int j = 0; j < n; ++j) {
                grid[i][j] = c;
            }
        }
    } else if (pattern == 2) {
        for (int j = 0; j < n; ++j) {
            char c = rnd.any(letters);
            for (int i = 0; i < n; ++i) {
                grid[i][j] = c;
            }
        }
    } else if (pattern == 3) {
        int offset = rnd.next(4);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = letters[(i + j + offset) % 4];
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = rnd.any(letters);
            }
        }
    }

    println(n, d);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
