#include "testlib.h"
#include <set>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Grid size
    int n = inf.readInt(1, 50, "n");
    inf.readEoln();

    // New circuit endpoints
    int r1 = inf.readInt(1, n, "r1");
    inf.readSpace();
    int c1 = inf.readInt(1, n, "c1");
    inf.readSpace();
    int r2 = inf.readInt(1, n, "r2");
    inf.readSpace();
    int c2 = inf.readInt(1, n, "c2");
    inf.readEoln();
    ensuref(!(r1 == r2 && c1 == c2),
            "Start and end of new circuit must differ, got (%d,%d) and (%d,%d)",
            r1, c1, r2, c2);

    // Cost on occupied cells
    int k = inf.readInt(2, 60, "k");
    inf.readEoln();

    // Number of existing circuits
    int m = inf.readInt(1, 7, "m");
    inf.readEoln();

    for (int i = 0; i < m; i++) {
        // Number of key vertices (start, turns, end)
        string ti_name = "t_" + to_string(i);
        int t = inf.readInt(2, 15, ti_name.c_str());

        // Read the t points
        vector<pair<int,int>> pts(t);
        for (int j = 0; j < t; j++) {
            inf.readSpace();
            string ri_name = "r_" + to_string(i) + "_" + to_string(j);
            int rr = inf.readInt(1, n, ri_name.c_str());
            inf.readSpace();
            string ci_name = "c_" + to_string(i) + "_" + to_string(j);
            int cc = inf.readInt(1, n, ci_name.c_str());
            pts[j] = {rr, cc};
        }
        inf.readEoln();

        // Check no self-crossing in this circuit
        set<pair<int,int>> localUsed;
        // mark the first cell
        localUsed.insert(pts[0]);
        // Walk each segment
        for (int j = 1; j < t; j++) {
            int r0 = pts[j-1].first, c0 = pts[j-1].second;
            int r1p = pts[j].first, c1p = pts[j].second;
            // Must move
            ensuref(!(r0 == r1p && c0 == c1p),
                    "Zero-length segment in circuit %d between points %d and %d: (%d,%d) to (%d,%d)",
                    i, j-1, j, r0, c0, r1p, c1p);
            // Must be axis-aligned
            bool sameRow = (r0 == r1p);
            bool sameCol = (c0 == c1p);
            ensuref(sameRow ^ sameCol,
                    "Non-axis-aligned segment in circuit %d between points %d and %d: (%d,%d) to (%d,%d)",
                    i, j-1, j, r0, c0, r1p, c1p);
            int dr = (r1p > r0 ? 1 : (r1p < r0 ? -1 : 0));
            int dc = (c1p > c0 ? 1 : (c1p < c0 ? -1 : 0));
            int len = sameRow ? abs(c1p - c0) : abs(r1p - r0);
            // Walk through cells on this segment (excluding the start point)
            for (int step = 1; step <= len; step++) {
                int rr = r0 + dr * step;
                int cc = c0 + dc * step;
                pair<int,int> cell = {rr, cc};
                ensuref(!localUsed.count(cell),
                        "Self-crossing in circuit %d at cell (%d,%d)",
                        i, rr, cc);
                localUsed.insert(cell);
            }
        }
    }

    inf.readEof();
    return 0;
}
