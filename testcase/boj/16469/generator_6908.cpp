#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid dimensions: small to medium
    int R = rnd.next(2, 15);
    int C = rnd.next(2, 15);

    // Wall density hyper-parameter with bias to extremes and mid
    int bias = rnd.next(-3, 3);
    // rnd.wnext(101, bias) gives 0..100, biased
    double density = rnd.wnext(101, bias) / 100.0;

    // Build grid with walls ('1') and open ('0')
    vector<string> grid(R, string(C, '0'));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (rnd.next() < density) grid[i][j] = '1';
            else grid[i][j] = '0';
        }
    }

    // Collect open cells
    vector<pair<int,int>> cells;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == '0')
                cells.emplace_back(i, j);
        }
    }

    // Ensure at least 3 open cells
    if ((int)cells.size() < 3) {
        // pick arbitrary cells to open
        vector<pair<int,int>> all;
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                all.emplace_back(i, j);
        shuffle(all.begin(), all.end());
        for (int k = 0; k < 3; k++) {
            int x = all[k].first, y = all[k].second;
            grid[x][y] = '0';
        }
        cells.clear();
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                if (grid[i][j] == '0')
                    cells.emplace_back(i, j);
    }

    // Choose distinct start positions
    shuffle(cells.begin(), cells.end());
    vector<pair<int,int>> start(3);
    start[0] = cells[0];
    start[1] = cells[1];
    start[2] = cells[2];

    // Output
    println(R, C);
    for (int i = 0; i < R; i++) {
        println(grid[i]);
    }
    // Convert to 1-based
    for (int k = 0; k < 3; k++) {
        printf("%d %d\n", start[k].first + 1, start[k].second + 1);
    }

    return 0;
}
