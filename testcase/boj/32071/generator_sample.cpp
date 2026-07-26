#include "testlib.h"
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int shape = rnd.next(0, 2);
    int n = shape == 0 ? 1 : rnd.next(2, 12);
    int m = shape == 1 ? 1 : rnd.next(2, 12);
    vector<string> grid(n, string(m, '0'));

    int pattern = rnd.next(0, 4);
    double density[] = {0.1, 0.35, 0.7, 0.95};
    int offset = rnd.next(0, 3);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            bool white = pattern < 4 ? rnd.next() < density[pattern]
                                     : (i + j + offset) % 4 == 0;
            grid[i][j] = white ? '1' : '0';
        }
    }

    vector<pair<int, int>> cells;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cells.emplace_back(i, j);
        }
    }
    shuffle(cells.begin(), cells.end());
    grid[cells[0].first][cells[0].second] = '1';
    grid[cells[1].first][cells[1].second] = '1';

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }
}
