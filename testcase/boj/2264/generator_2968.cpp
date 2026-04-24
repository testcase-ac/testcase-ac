#include "testlib.h"
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Maximum number of points
    const int Nmax = 10;
    // Randomly decide symmetry probability
    double symProb = rnd.next();
    bool makeSym = rnd.next() < symProb;

    vector<pair<int,int>> pts;
    if (makeSym) {
        // Generate a symmetric set about x = mid
        int mid = rnd.next(-5, 5);
        // Hyper-parameters for diversity
        int maxPairs = Nmax / 2;
        int numPairs = rnd.next(0, maxPairs);
        int numOn    = rnd.next(0, 2); // points exactly on the fold line
        // Ensure at least one point
        if (numPairs == 0 && numOn == 0) numOn = 1;
        int yRange  = rnd.next(1, 5);
        int dxRange = rnd.next(1, 5);
        // Mirror pairs
        for (int i = 0; i < numPairs; i++) {
            int y  = rnd.next(-yRange, yRange);
            int dx = rnd.next(1, dxRange);
            pts.emplace_back(mid + dx, y);
            pts.emplace_back(mid - dx, y);
        }
        // Points on the fold line
        for (int i = 0; i < numOn; i++) {
            int y = rnd.next(-yRange, yRange);
            pts.emplace_back(mid, y);
        }
    } else {
        // Generate a clearly non-symmetric set
        int N = rnd.next(2, Nmax);
        int xRange = rnd.next(1, 5);
        int yRange = rnd.next(1, 5);
        pts.reserve(N);
        for (int i = 0; i < N; i++) {
            int x = rnd.next(-xRange, xRange);
            int y = rnd.next(-yRange, yRange);
            pts.emplace_back(x, y);
        }
        // Force a break in symmetry: two points with different y
        int dy = rnd.next(1, yRange) * (rnd.next() < 0.5 ? 1 : -1);
        pts[1].second = pts[0].second + dy;
    }

    // Shuffle the order of points
    shuffle(pts.begin(), pts.end());

    // Output
    println((int)pts.size());
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}
