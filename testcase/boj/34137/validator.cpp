#include "testlib.h"
#include <vector>
#include <map>
#include <algorithm>
#include <set>
using namespace std;

struct Structure {
    int r, s, e, c;
    int idx;
    Structure(int r, int s, int e, int c, int idx): r(r), s(s), e(e), c(c), idx(idx) {}
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, M, T, K
    int N = inf.readInt(2, 1000000000, "N");
    inf.readSpace();
    int M = inf.readInt(2, 200000, "M");
    inf.readSpace();
    int T = inf.readInt(1, 200000, "T");
    inf.readSpace();
    int K = inf.readInt(0, 200000, "K");
    inf.readEoln();

    // 2. Read a_1..a_M
    vector<int> A = inf.readInts(M, 1, T, "a_i");
    inf.readEoln();

    // 3. Read K structures
    // For each row r, store intervals [s,e] for that row
    // To check for overlap, store for each r a vector of intervals, and check for overlap as we insert
    map<int, vector<pair<int,int>>> row_intervals;
    for (int i = 0; i < K; ++i) {
        int r = inf.readInt(2, N, "r_i");
        inf.readSpace();
        int s = inf.readInt(1, M, "s_i");
        inf.readSpace();
        int e = inf.readInt(s, M, "e_i");
        inf.readSpace();
        int c = inf.readInt(1, T, "c_i");
        inf.readEoln();

        // Check for overlap in this row
        auto& intervals = row_intervals[r];
        // Insert and check for overlap
        // Since intervals are few per row, linear scan is fine
        for (size_t j = 0; j < intervals.size(); ++j) {
            int s2 = intervals[j].first;
            int e2 = intervals[j].second;
            // Overlap if not (e < s2 or e2 < s)
            bool overlap = !(e < s2 || e2 < s);
            ensuref(!overlap, 
                "Overlapping structures at row %d: intervals [%d,%d] and [%d,%d] (structure indices %d and %d)",
                r, s2, e2, s, e, (int)j+1, i+1);
        }
        intervals.emplace_back(s, e);
    }

    inf.readEof();
}
