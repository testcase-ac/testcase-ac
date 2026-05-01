#include "testlib.h"
#include <vector>
#include <string>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Grid size hyper-parameter: bias towards small or large
    int t_n = rnd.next(-2, 2);
    int n = rnd.wnext(10, t_n) + 1;  // 1 ≤ n ≤ 10
    int total = n * n;
    // Number of mines hyper-parameter: bias distribution
    int t_m = rnd.next(-1, 1);
    int m = rnd.wnext(total + 1, t_m);  // 0 ≤ m ≤ total
    // Prepare all cells and shuffle
    vector<pair<int,int>> cells;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cells.emplace_back(i, j);
    shuffle(cells.begin(), cells.end());
    // Assign mines
    vector<string> mineMap(n, string(n, '.'));
    vector<pair<int,int>> safeCells;
    for (int idx = 0; idx < total; idx++) {
        int x = cells[idx].first, y = cells[idx].second;
        if (idx < m)
            mineMap[x][y] = '*';
        else
            safeCells.emplace_back(x, y);
    }
    // Number of opened safe cells hyper-parameter
    int t_k = rnd.next(-1, 1);
    int k_safe = rnd.wnext((int)safeCells.size() + 1, t_k);  // 0 ≤ k_safe ≤ safeCells.size()
    shuffle(safeCells.begin(), safeCells.end());
    // Build open map: open only safe cells
    vector<string> openMap(n, string(n, '.'));
    for (int i = 0; i < k_safe; i++) {
        int x = safeCells[i].first, y = safeCells[i].second;
        openMap[x][y] = 'x';
    }
    // Output
    println(n);
    for (int i = 0; i < n; i++) println(mineMap[i]);
    for (int i = 0; i < n; i++) println(openMap[i]);
    return 0;
}
