#include "testlib.h"
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R, C, K
    long long R = inf.readLong(1LL, 1000000000LL, "R");
    inf.readSpace();
    long long C = inf.readLong(2LL, 1000000000LL, "C");
    inf.readSpace();
    int K = inf.readInt(0, 1000, "K");
    inf.readEoln();

    // Collect blocked cells, ensure no duplicates and in range
    map<long long, vector<long long>> blocks;
    set<pair<long long, long long>> seen;
    for (int i = 0; i < K; i++) {
        long long r = inf.readLong(1LL, R, "row");
        inf.readSpace();
        long long c = inf.readLong(1LL, C, "col");
        inf.readEoln();
        pair<long long,long long> p = make_pair(r, c);
        ensuref(!seen.count(p),
                "Duplicate broken-cell position at (%lld, %lld)", r, c);
        seen.insert(p);
        blocks[r].push_back(c);
    }

    // Validate that there is at least one place to put a 1x2 horizontal tile
    // A tile covers (r, j) and (r, j+1), both must be broken (i.e., not in 'blocks').
    // If there is any row with no blocked cells, since C>=2, it has at least one adjacent pair.
    bool ok = false;
    long long distinct_blocked_rows = (long long)blocks.size();
    if (R > distinct_blocked_rows) {
        // There's at least one row with zero blocked cells.
        ok = true;
    } else {
        // Every row has at least one blocked cell; check each for a gap of >=2 broken cells.
        for (auto &it : blocks) {
            vector<long long> &cols = it.second;
            sort(cols.begin(), cols.end());
            // Gap before the first blocked column
            if (cols[0] >= 3) {
                ok = true;
                break;
            }
            // Gaps between blocked columns
            for (size_t j = 1; j < cols.size(); j++) {
                long long gap = cols[j] - cols[j-1] - 1;
                if (gap >= 2) {
                    ok = true;
                    break;
                }
            }
            if (ok) break;
            // Gap after the last blocked column
            if (C - cols.back() >= 2) {
                ok = true;
                break;
            }
        }
    }
    ensuref(ok, "No place to put at least one 1x2 tile");

    inf.readEof();
    return 0;
}
