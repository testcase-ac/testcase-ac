#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid size
    int n = rnd.next(1, 10);
    // Upper bound on total stones
    int maxK = min(n * n, 20);

    // Choose generation variant
    int variant = rnd.next(1, 4);

    vector<pair<int,int>> cand;
    if (variant == 1) {
        // Uniform random stones
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                cand.emplace_back(i, j);
    } else if (variant == 2) {
        // Row-heavy: pick few rows, then random columns
        int rowCount = rnd.next(1, n);
        vector<int> rows(n);
        for (int i = 0; i < n; ++i) rows[i] = i + 1;
        shuffle(rows.begin(), rows.end());
        rows.resize(rowCount);
        for (int r : rows)
            for (int c = 1; c <= n; ++c)
                cand.emplace_back(r, c);
    } else if (variant == 3) {
        // Column-heavy: pick few columns, then random rows
        int colCount = rnd.next(1, n);
        vector<int> cols(n);
        for (int i = 0; i < n; ++i) cols[i] = i + 1;
        shuffle(cols.begin(), cols.end());
        cols.resize(colCount);
        for (int c : cols)
            for (int r = 1; r <= n; ++r)
                cand.emplace_back(r, c);
    } else {
        // Clustered around a center
        int centerR = rnd.next(1, n);
        int centerC = rnd.next(1, n);
        int radius = rnd.next(0, n - 1);
        for (int r = 1; r <= n; ++r) {
            for (int c = 1; c <= n; ++c) {
                int dr = r - centerR; if (dr < 0) dr = -dr;
                int dc = c - centerC; if (dc < 0) dc = -dc;
                if (max(dr, dc) <= radius) {
                    cand.emplace_back(r, c);
                }
            }
        }
    }

    // Select stones from candidates
    int ub = min((int)cand.size(), maxK);
    int k = rnd.next(1, ub);
    shuffle(cand.begin(), cand.end());
    cand.resize(k);

    // Output
    println(n, k);
    for (auto &p : cand)
        println(p.first, p.second);

    return 0;
}
