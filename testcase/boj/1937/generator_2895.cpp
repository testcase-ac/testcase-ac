#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // small size n
    int n = rnd.next(2, 4);
    vector<vector<int>> a(n, vector<int>(n, 0));

    // choose pattern for diversity
    int pattern = rnd.next(0, 2);
    if (pattern == 0) {
        // completely random values
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                a[i][j] = rnd.next(1, 20);
    }
    else if (pattern == 1) {
        // create a strictly increasing path
        int maxcells = n * n;
        int L = rnd.next(2, maxcells);
        vector<vector<bool>> used(n, vector<bool>(n, false));
        vector<pair<int,int>> path;
        int r = rnd.next(0, n-1), c = rnd.next(0, n-1);
        used[r][c] = true;
        path.emplace_back(r, c);
        while ((int)path.size() < L) {
            vector<pair<int,int>> nbr;
            static int dr[4] = {1,-1,0,0}, dc[4] = {0,0,1,-1};
            for (int d = 0; d < 4; d++){
                int nr = r + dr[d], nc = c + dc[d];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && !used[nr][nc])
                    nbr.emplace_back(nr, nc);
            }
            if (nbr.empty()) break;
            auto nxt = rnd.any(nbr);
            r = nxt.first; c = nxt.second;
            used[r][c] = true;
            path.emplace_back(r, c);
        }
        // assign increasing values along path
        int cur = rnd.next(1, 5);
        for (auto &p : path) {
            a[p.first][p.second] = cur;
            cur += rnd.next(1, 3);
        }
        // fill others
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (!used[i][j]) {
                    a[i][j] = rnd.next(1, cur);
                }
            }
        }
    }
    else {
        // row-monotonic: each row strictly larger than previous
        int base = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = base + rnd.next(0, 3);
            }
            base += 5;
        }
    }

    // output
    println(n);
    for (int i = 0; i < n; i++) {
        println(a[i]);
    }
    return 0;
}
