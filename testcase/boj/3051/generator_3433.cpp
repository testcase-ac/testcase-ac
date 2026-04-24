#include "testlib.h"
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // number of trenches
    int N = rnd.next(1, 10);
    // hyper-parameters for diversity
    double p_share = rnd.next(0.0, 1.0);
    double p_diag  = rnd.next(0.0, 1.0);
    double p_col   = rnd.next(0.0, 1.0);

    vector<array<int,4>> segs;
    // directions for diagonal segments
    vector<pair<int,int>> dirs = {{1,1},{1,-1},{-1,1},{-1,-1}};

    for (int i = 0; i < N; i++) {
        int x0, y0, x1, y1;
        // share an endpoint of an existing segment
        if (i > 0 && rnd.next() < p_share) {
            int j = rnd.next(0, i - 1);
            auto s = segs[j];
            if (rnd.next(0,1) == 0) {
                x0 = s[0]; y0 = s[1];
            } else {
                x0 = s[2]; y0 = s[3];
            }
            // ensure non-degenerate
            do {
                x1 = rnd.next(0, 10);
                y1 = rnd.next(0, 10);
            } while (x1 == x0 && y1 == y0);
            segs.push_back({x0, y0, x1, y1});
            continue;
        }
        // diagonal segment
        if (rnd.next() < p_diag) {
            auto d = rnd.any(dirs);
            int L = rnd.next(1, 10);
            int dx = d.first, dy = d.second;
            // ensure within [0,10]
            int xmin = max(0, -dx * L), xmax = 10 - max(0, dx * L);
            int ymin = max(0, -dy * L), ymax = 10 - max(0, dy * L);
            x0 = rnd.next(xmin, xmax);
            y0 = rnd.next(ymin, ymax);
            x1 = x0 + dx * L;
            y1 = y0 + dy * L;
            segs.push_back({x0, y0, x1, y1});
            continue;
        }
        // axis-aligned segment
        if (rnd.next() < 0.5) {
            // horizontal
            bool did = false;
            if (rnd.next() < p_col) {
                vector<int> hidx;
                for (int j = 0; j < (int)segs.size(); j++)
                    if (segs[j][1] == segs[j][3])
                        hidx.push_back(j);
                if (!hidx.empty()) {
                    int j = rnd.any(hidx);
                    int y = segs[j][1];
                    int mn = min(segs[j][0], segs[j][2]), mx = max(segs[j][0], segs[j][2]);
                    int lo = max(0, mn - 2), hi = min(10, mx + 2);
                    do {
                        x0 = rnd.next(lo, hi);
                        x1 = rnd.next(lo, hi);
                    } while (x0 == x1);
                    y0 = y1 = y;
                    segs.push_back({x0, y0, x1, y1});
                    did = true;
                }
            }
            if (!did) {
                y0 = rnd.next(0, 10);
                do {
                    x0 = rnd.next(0, 10);
                    x1 = rnd.next(0, 10);
                } while (x0 == x1);
                y1 = y0;
                segs.push_back({x0, y0, x1, y1});
            }
        } else {
            // vertical
            bool did = false;
            if (rnd.next() < p_col) {
                vector<int> vidx;
                for (int j = 0; j < (int)segs.size(); j++)
                    if (segs[j][0] == segs[j][2])
                        vidx.push_back(j);
                if (!vidx.empty()) {
                    int j = rnd.any(vidx);
                    int x = segs[j][0];
                    int mn = min(segs[j][1], segs[j][3]), mx = max(segs[j][1], segs[j][3]);
                    int lo = max(0, mn - 2), hi = min(10, mx + 2);
                    do {
                        y0 = rnd.next(lo, hi);
                        y1 = rnd.next(lo, hi);
                    } while (y0 == y1);
                    x0 = x1 = x;
                    segs.push_back({x0, y0, x1, y1});
                    did = true;
                }
            }
            if (!did) {
                x0 = rnd.next(0, 10);
                do {
                    y0 = rnd.next(0, 10);
                    y1 = rnd.next(0, 10);
                } while (y0 == y1);
                x1 = x0;
                segs.push_back({x0, y0, x1, y1});
            }
        }
    }

    // output
    println(N);
    for (auto &s : segs) {
        println(s[0], s[1], s[2], s[3]);
    }
    return 0;
}
