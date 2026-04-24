#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of points
    int N = rnd.next(4, 10);

    // How many rectangles to inject (axis-aligned)
    int maxRects = N / 4;
    double pRect = rnd.next(); // in [0,1)
    int Krect;
    if (pRect < 0.2) Krect = 0;
    else if (pRect < 0.6) Krect = min(1, maxRects);
    else if (pRect < 0.8) Krect = min(2, maxRects);
    else Krect = rnd.next(0, maxRects);
    Krect = min(Krect, maxRects);

    // Coordinate bound hyper-parameter
    int cBound;
    double pr = rnd.next();
    if (pr < 0.3) cBound = rnd.next(5, 10);
    else if (pr < 0.7) cBound = rnd.next(10, 50);
    else cBound = rnd.next(50, 100);

    // Cluster vs uniform distribution for noise points
    bool cluster = rnd.next() < 0.5;
    int cx = rnd.next(-cBound, cBound);
    int cy = rnd.next(-cBound, cBound);

    set<pair<int,int>> seen;
    vector<pair<int,int>> pts;

    // Inject axis-aligned rectangles
    for (int i = 0; i < Krect; ++i) {
        int x1 = rnd.next(-cBound, cBound);
        int x2 = rnd.next(-cBound, cBound);
        if (x1 == x2) {
            if (x1 < cBound) x2 = x1 + 1;
            else x2 = x1 - 1;
        }
        int y1 = rnd.next(-cBound, cBound);
        int y2 = rnd.next(-cBound, cBound);
        if (y1 == y2) {
            if (y1 < cBound) y2 = y1 + 1;
            else y2 = y1 - 1;
        }
        // Four corners
        pair<int,int> c1 = {x1, y1};
        pair<int,int> c2 = {x1, y2};
        pair<int,int> c3 = {x2, y1};
        pair<int,int> c4 = {x2, y2};
        for (auto p : {c1, c2, c3, c4}) {
            if (seen.insert(p).second) {
                pts.push_back(p);
            }
        }
    }

    // Fill remaining points
    while ((int)pts.size() < N) {
        int x, y;
        if (cluster) {
            int xl = max(-cBound, cx - 5);
            int xr = min(cBound, cx + 5);
            int yl = max(-cBound, cy - 5);
            int yr = min(cBound, cy + 5);
            x = rnd.next(xl, xr);
            y = rnd.next(yl, yr);
        } else {
            x = rnd.next(-cBound, cBound);
            y = rnd.next(-cBound, cBound);
        }
        if (seen.insert({x, y}).second) {
            pts.emplace_back(x, y);
        }
    }

    // Shuffle and output
    shuffle(pts.begin(), pts.end());
    println(N);
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}
