#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // grid size
    int n = rnd.next(2, 10);
    int m = rnd.next(2, 10);
    // block probability hyper-parameter: sometimes heavy, sometimes light
    double p;
    if (rnd.next(0, 1) == 0) {
        // favor fewer blocks
        p = rnd.wnext(101, -2) / 100.0;
    } else {
        // favor more blocks
        p = rnd.wnext(101, 2) / 100.0;
    }
    // choose target position: sometimes center, sometimes corner, otherwise random
    int tx, ty;
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        // center-ish
        tx = n / 2;
        ty = m / 2;
    } else if (mode == 1) {
        // corner
        int c = rnd.next(0, 3);
        tx = (c & 1) ? n - 1 : 0;
        ty = (c & 2) ? m - 1 : 0;
    } else {
        // anywhere
        tx = rnd.next(0, n - 1);
        ty = rnd.next(0, m - 1);
    }
    // build grid
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == tx && j == ty) {
                a[i][j] = 2;
            } else {
                a[i][j] = (rnd.next() < p ? 0 : 1);
            }
        }
    }
    // ensure at least one neighbor of target is reachable
    static int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    vector<pair<int,int>> neigh;
    bool anyReachable = false;
    for (auto &d : dirs) {
        int ni = tx + d[0], nj = ty + d[1];
        if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
            neigh.emplace_back(ni, nj);
            if (a[ni][nj] == 1) anyReachable = true;
        }
    }
    if (!anyReachable && !neigh.empty()) {
        auto pr = rnd.any(neigh);
        a[pr.first][pr.second] = 1;
    }
    // output
    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }
    return 0;
}
