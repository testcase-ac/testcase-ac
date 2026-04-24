#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose grid size
    int n = rnd.next(2, 10);

    // Prepare empty grid
    vector<string> grid(n, string(n, '0'));

    // Scenario type for diversity
    int type = rnd.next(0, 2);

    if (type == 0) {
        // Random independent cells with density p of white
        int pPct = rnd.next(10, 90); // percentage of black cells
        double pb = pPct / 100.0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                grid[i][j] = (rnd.next() < pb ? '0' : '1');
            }
        }
    }
    else if (type == 1) {
        // Mostly white: place a few blacks
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                grid[i][j] = '1';
        // choose k black cells
        int maxk = max(1, n);
        int k = rnd.next(1, maxk);
        vector<pair<int,int>> cells;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (!(i == 0 && j == 0) && !(i == n-1 && j == n-1))
                    cells.emplace_back(i, j);
        shuffle(cells.begin(), cells.end());
        for (int t = 0; t < k && t < (int)cells.size(); t++) {
            auto [i, j] = cells[t];
            grid[i][j] = '0';
        }
    }
    else {
        // Sparse: only a random path is white, rest black, plus a few extra whites
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                grid[i][j] = '0';
        // build a random monotone path from (0,0) to (n-1,n-1)
        vector<char> moves;
        for (int i = 0; i < n-1; i++) moves.push_back('R');
        for (int i = 0; i < n-1; i++) moves.push_back('D');
        shuffle(moves.begin(), moves.end());
        int ci = 0, cj = 0;
        grid[0][0] = '1';
        vector<pair<int,int>> path;
        path.emplace_back(0,0);
        for (char c : moves) {
            if (c == 'R') cj++;
            else ci++;
            grid[ci][cj] = '1';
            path.emplace_back(ci, cj);
        }
        // Add some extra random whites
        int extra = rnd.next(0, n);
        vector<pair<int,int>> others;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == '0')
                    others.emplace_back(i, j);
        shuffle(others.begin(), others.end());
        for (int t = 0; t < extra && t < (int)others.size(); t++) {
            auto [i, j] = others[t];
            grid[i][j] = '1';
        }
    }

    // Ensure start and end are white
    grid[0][0] = '1';
    grid[n-1][n-1] = '1';

    // Output
    println(n);
    for (int i = 0; i < n; i++) {
        println(grid[i]);
    }
    return 0;
}
