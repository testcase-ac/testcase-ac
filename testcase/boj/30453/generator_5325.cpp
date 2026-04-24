#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter: coordinate bound
    int B = rnd.next(1, 10);

    // Choose an integer center for symmetry pairs
    int cx = rnd.next(-B, B);
    int cy = rnd.next(-B, B);

    // Number of symmetric pairs and standalone points
    int maxPairs = min(5, B);
    int nPairs = rnd.next(0, maxPairs);
    int maxSingles = min(5, B);
    int nSingles = rnd.next(0, maxSingles);
    if (nPairs == 0 && nSingles == 0) {
        nSingles = 1;
    }

    set<pair<int,int>> used;
    vector<pair<int,int>> pts;

    // Generate symmetric pairs around (cx, cy)
    for (int i = 0; i < nPairs; i++) {
        int x1, y1, x2, y2;
        for (;;) {
            x1 = rnd.next(-B, B);
            y1 = rnd.next(-B, B);
            x2 = 2 * cx - x1;
            y2 = 2 * cy - y1;
            // must be distinct and unused
            if (x1 == x2 && y1 == y2) continue;
            if (used.count({x1, y1})) continue;
            if (used.count({x2, y2})) continue;
            break;
        }
        used.insert({x1, y1});
        used.insert({x2, y2});
        pts.emplace_back(x1, y1);
        pts.emplace_back(x2, y2);
    }

    // Generate standalone points (they count as symmetric to themselves)
    for (int i = 0; i < nSingles; i++) {
        int x, y;
        for (;;) {
            x = rnd.next(-B, B);
            y = rnd.next(-B, B);
            if (!used.count({x, y})) break;
        }
        used.insert({x, y});
        pts.emplace_back(x, y);
    }

    // Shuffle for randomness
    shuffle(pts.begin(), pts.end());

    // Output the test case
    int n = pts.size();
    println(n);
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}
