#include "testlib.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // We expect exactly 3 points
    vector<pair<int,int>> pts;
    vector<string> xnames = {"x1", "x2", "x3"};
    vector<string> ynames = {"y1", "y2", "y3"};
    for (int i = 0; i < 3; ++i) {
        int x = inf.readInt(1, 1000, xnames[i].c_str());
        inf.readSpace();
        int y = inf.readInt(1, 1000, ynames[i].c_str());
        inf.readEoln();
        pts.emplace_back(x, y);
    }

    // Points must be pairwise distinct
    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            ensuref(pts[i] != pts[j],
                    "Duplicate points at indices %d and %d: (%d,%d)",
                    i+1, j+1, pts[i].first, pts[i].second);
        }
    }

    // Count frequencies of x and y coordinates
    map<int,int> cx, cy;
    for (auto &p : pts) {
        cx[p.first]++;
        cy[p.second]++;
    }

    // For an axis-aligned rectangle missing one corner, there must be exactly
    // two distinct x-coordinates and two distinct y-coordinates,
    // with frequencies {1,2} on each axis.
    ensuref((int)cx.size() == 2,
            "Number of distinct x-coordinates is %d, but should be 2",
            (int)cx.size());
    ensuref((int)cy.size() == 2,
            "Number of distinct y-coordinates is %d, but should be 2",
            (int)cy.size());

    // Check that the frequency multiset is {1,2}
    {
        vector<int> fx;
        for (auto &kv : cx) fx.push_back(kv.second);
        sort(fx.begin(), fx.end());
        ensuref(fx.size() == 2 && fx[0] == 1 && fx[1] == 2,
                "Invalid x-coordinate frequencies: [%d, %d], expected [1,2]",
                fx[0], fx[1]);
    }
    {
        vector<int> fy;
        for (auto &kv : cy) fy.push_back(kv.second);
        sort(fy.begin(), fy.end());
        ensuref(fy.size() == 2 && fy[0] == 1 && fy[1] == 2,
                "Invalid y-coordinate frequencies: [%d, %d], expected [1,2]",
                fy[0], fy[1]);
    }

    // No extra data
    inf.readEof();
    return 0;
}
