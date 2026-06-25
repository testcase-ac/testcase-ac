#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == 0) {
            n = 2;
        } else if (tc == 1) {
            n = 10;
        } else {
            n = rnd.next(2, 10);
        }

        int rowStep = rnd.next(1, 7);
        int colStep = rnd.next(1, 7);
        int base = rnd.next(1, 2500 - (n - 1) * (rowStep + colStep));

        vector<vector<int>> grid(n, vector<int>(n));
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                grid[r][c] = base + r * rowStep + c * colStep;
            }
        }

        vector<vector<int>> lists;
        for (int r = 0; r < n; ++r) {
            lists.push_back(grid[r]);
        }
        for (int c = 0; c < n; ++c) {
            vector<int> column;
            for (int r = 0; r < n; ++r) {
                column.push_back(grid[r][c]);
            }
            lists.push_back(column);
        }

        int missing = rnd.next(0, 2 * n - 1);
        lists.erase(lists.begin() + missing);
        shuffle(lists.begin(), lists.end());

        println(n);
        for (const vector<int>& list : lists) {
            println(list);
        }
    }

    return 0;
}
