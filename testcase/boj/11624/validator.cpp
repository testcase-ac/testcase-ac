#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read n, m
    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100, "m");
    inf.readEoln();

    // 2. Read pattern
    vector<string> pattern(n);
    for (int i = 0; i < n; ++i) {
        pattern[i] = inf.readLine("[.#]{"+to_string(m)+","+to_string(m)+"}", "pattern_row");
        ensuref((int)pattern[i].size() == m, "Row %d: pattern row length is not %d", i+1, m);
        for (int j = 0; j < m; ++j) {
            ensuref(pattern[i][j] == '.' || pattern[i][j] == '#', "Invalid character '%c' at pattern[%d][%d]", pattern[i][j], i+1, j+1);
        }
    }

    // 3. Read q
    int q = inf.readInt(1, 200000, "q");
    inf.readEoln();

    // 4. Read q queries, and check that all starting cells and origin are empty
    set<pair<int,int>> checked_cells; // To avoid redundant checks
    vector<pair<int,int>> queries(q);
    for (int i = 0; i < q; ++i) {
        long long r = inf.readLong(-1000000000LL, 1000000000LL, "r");
        inf.readSpace();
        long long c = inf.readLong(-1000000000LL, 1000000000LL, "c");
        inf.readEoln();

        // Check that the mapped cell is empty
        int rr = ((r % n) + n) % n;
        int cc = ((c % m) + m) % m;
        ensuref(pattern[rr][cc] == '.', "Query %d: starting cell (%lld, %lld) maps to blocked pattern cell (%d, %d)", i+1, r, c, rr, cc);

        // Save for later (for possible further checks)
        queries[i] = make_pair(rr, cc);

        // Optionally, check only once per cell
        checked_cells.insert({rr, cc});
    }

    // 5. Check that the origin is empty
    ensuref(pattern[0][0] == '.', "Origin (0,0) is not empty");

    // 6. Check that at least one empty cell exists in the pattern
    bool has_empty = false;
    for (int i = 0; i < n && !has_empty; ++i)
        for (int j = 0; j < m && !has_empty; ++j)
            if (pattern[i][j] == '.')
                has_empty = true;
    ensuref(has_empty, "Pattern contains no empty cells");

    // 7. Check that all lines/spacing are correct (already done above)
    inf.readEof();
}
