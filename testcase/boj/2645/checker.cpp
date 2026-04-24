#include "testlib.h"
#include <vector>
#include <climits>
using namespace std;

int n, k;
int sr, sc, tr, tc;
vector<vector<bool>> occupied;

int sgn(int x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

// Read an answer (jury or contestant), verify the path, compute its cost, and return it.
// The answer format: first line is the reported cost, second line is the path:
//   an integer cnt (>=2), then cnt pairs (r, c).
// If anything is wrong in the path or the reported cost doesn't match computed cost,
// quit with _wa for ouf, or _fail for ans.
int readAns(InStream &stream) {
    // read reported cost
    int reported = stream.readInt(0, INT_MAX, "reported cost");
    // read path description
    int cnt = stream.readInt(2, n * n, "number of key cells");
    vector<pair<int,int>> key(cnt);
    for (int i = 0; i < cnt; i++) {
        int r = stream.readInt(1, n, format("row[%d]", i+1).c_str());
        int c = stream.readInt(1, n, format("col[%d]", i+1).c_str());
        key[i] = make_pair(r, c);
    }
    // check endpoints
    if (key[0].first != sr || key[0].second != sc) {
        stream.quitf(_wa, "path does not start at the required start (%d,%d), found (%d,%d)",
                    sr, sc, key[0].first, key[0].second);
    }
    if (key.back().first != tr || key.back().second != tc) {
        stream.quitf(_wa, "path does not end at the required end (%d,%d), found (%d,%d)",
                    tr, tc, key.back().first, key.back().second);
    }
    // used mask to forbid revisits
    vector<vector<bool>> used(n+1, vector<bool>(n+1, false));
    int computed = 0;
    // traverse segments
    for (int i = 0; i + 1 < cnt; i++) {
        int r1 = key[i].first, c1 = key[i].second;
        int r2 = key[i+1].first, c2 = key[i+1].second;
        // must be in same row or same column
        if (r1 != r2 && c1 != c2) {
            stream.quitf(_wa, "key cells %d and %d are not aligned: (%d,%d)->(%d,%d)",
                        i+1, i+2, r1, c1, r2, c2);
        }
        int dr = sgn(r2 - r1);
        int dc = sgn(c2 - c1);
        int steps = max(abs(r2 - r1), abs(c2 - c1));
        for (int step = 0; step <= steps; step++) {
            if (i > 0 && step == 0) continue; // skip overlapping key
            int rr = r1 + dr * step;
            int cc = c1 + dc * step;
            // bounds check (redundant since input cells in [1,n], line is straight)
            if (rr < 1 || rr > n || cc < 1 || cc > n) {
                stream.quitf(_wa, "cell (%d,%d) is out of grid", rr, cc);
            }
            if (used[rr][cc]) {
                stream.quitf(_wa, "cell (%d,%d) is visited more than once", rr, cc);
            }
            used[rr][cc] = true;
            computed += (occupied[rr][cc] ? k : 1);
        }
    }
    // check reported vs computed
    if (reported != computed) {
        stream.quitf(_wa, "reported cost %d does not match computed cost %d", reported, computed);
    }
    return computed;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    // read input
    n = inf.readInt();
    sr = inf.readInt(); sc = inf.readInt();
    tr = inf.readInt(); tc = inf.readInt();
    k = inf.readInt();
    int m = inf.readInt();
    occupied.assign(n+1, vector<bool>(n+1, false));
    // mark existing circuits
    for (int i = 0; i < m; i++) {
        int cnt = inf.readInt(2, n*n);
        vector<pair<int,int>> key(cnt);
        for (int j = 0; j < cnt; j++) {
            key[j].first = inf.readInt(1, n);
            key[j].second = inf.readInt(1, n);
        }
        for (int j = 0; j + 1 < cnt; j++) {
            int r1 = key[j].first, c1 = key[j].second;
            int r2 = key[j+1].first, c2 = key[j+1].second;
            int dr = sgn(r2 - r1), dc = sgn(c2 - c1);
            int steps = max(abs(r2 - r1), abs(c2 - c1));
            for (int step = 0; step <= steps; step++) {
                int rr = r1 + dr * step;
                int cc = c1 + dc * step;
                occupied[rr][cc] = true;
            }
        }
    }
    // read and check jury answer
    int jans = readAns(ans);
    // read and check participant answer
    int pans = readAns(ouf);
    // ensure no extra output
    ouf.readEof();
    // compare
    if (pans > jans) {
        quitf(_wa, "participant's cost %d is worse than jury's %d", pans, jans);
    } else if (pans < jans) {
        quitf(_fail, "participant found a better cost %d than jury's %d", pans, jans);
    } else {
        quitf(_ok, "cost = %d", pans);
    }
    return 0;
}
