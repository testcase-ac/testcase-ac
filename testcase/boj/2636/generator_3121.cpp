#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid dimensions (at least 5x5 to allow holes)
    int R = rnd.next(5, 12);
    int C = rnd.next(5, 12);

    // Initialize all cells to air (0)
    vector<vector<int>> a(R, vector<int>(C, 0));

    // Fill interior with cheese (1) with probability p in [0.2, 0.8]
    double p = rnd.next() * 0.6 + 0.2;
    for (int i = 1; i < R - 1; i++) {
        for (int j = 1; j < C - 1; j++) {
            a[i][j] = (rnd.next() < p ? 1 : 0);
        }
    }

    // Ensure at least one cheese cell exists
    vector<pair<int,int>> cells;
    for (int i = 1; i < R - 1; i++)
        for (int j = 1; j < C - 1; j++)
            cells.emplace_back(i, j);

    bool hasCheese = false;
    for (auto &pr : cells) {
        if (a[pr.first][pr.second] == 1) {
            hasCheese = true;
            break;
        }
    }
    if (!hasCheese) {
        shuffle(cells.begin(), cells.end());
        auto pr = cells[0];
        a[pr.first][pr.second] = 1;
    }

    // Optionally carve a fully enclosed hole
    if (rnd.next() < 0.5 && R >= 5 && C >= 5) {
        // Choose a ring boundary at least 2 cells wide
        int x1 = rnd.next(1, R - 4);
        int x2 = rnd.next(x1 + 2, R - 2);
        int y1 = rnd.next(1, C - 4);
        int y2 = rnd.next(y1 + 2, C - 2);

        // Build the cheese ring
        for (int x = x1; x <= x2; x++) {
            a[x][y1] = 1;
            a[x][y2] = 1;
        }
        for (int y = y1; y <= y2; y++) {
            a[x1][y] = 1;
            a[x2][y] = 1;
        }

        // Carve out the interior hole
        for (int x = x1 + 1; x < x2; x++)
            for (int y = y1 + 1; y < y2; y++)
                a[x][y] = 0;
    }

    // Output the test case
    println(R, C);
    for (int i = 0; i < R; i++) {
        println(a[i]);
    }

    return 0;
}
