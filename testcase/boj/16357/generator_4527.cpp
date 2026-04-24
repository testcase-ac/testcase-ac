#include "testlib.h"
#include <vector>
#include <set>
#include <array>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of rectangles
    int N = rnd.next(3, 10);
    // Hyper-parameters for coordinate bounds
    int Xb = rnd.any(vector<int>{10, 20, 50});
    int Yb = rnd.any(vector<int>{10, 20, 50});
    // Build a set of candidate y-coordinates for diversity
    int candidateYCount = rnd.next(2, 5);
    set<int> ySet;
    while ((int)ySet.size() < candidateYCount) {
        ySet.insert(rnd.next(-Yb, Yb));
    }
    vector<int> candidateYs(ySet.begin(), ySet.end());
    // Generate rectangles
    vector<array<int,4>> rects;
    for (int i = 0; i < N; i++) {
        bool useCand = rnd.next(0, 1);
        int uy, vy;
        if (useCand) {
            // pick two distinct candidate y's
            int a = rnd.next(0, (int)candidateYs.size() - 1);
            int b = rnd.next(0, (int)candidateYs.size() - 2);
            if (b >= a) b++;
            int y1 = candidateYs[a], y2 = candidateYs[b];
            uy = max(y1, y2);
            vy = min(y1, y2);
        } else {
            // pick random y-interval
            vy = rnd.next(-Yb, Yb - 1);
            uy = rnd.next(vy + 1, Yb);
        }
        // pick random x-interval
        int ux = rnd.next(-Xb, Xb - 1);
        int vx = rnd.next(ux + 1, Xb);
        rects.push_back({ux, uy, vx, vy});
    }
    // Shuffle to avoid any ordering bias
    shuffle(rects.begin(), rects.end());
    // Output
    println(N);
    for (auto &r : rects) {
        println(r[0], r[1], r[2], r[3]);
    }
    return 0;
}
