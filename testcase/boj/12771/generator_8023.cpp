#include "testlib.h"
#include <vector>
#include <tuple>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of deposits
    int n = rnd.next(1, 12);
    // Number of distinct layers
    int L = rnd.next(1, min(n, 5));

    // Sample unique y-coordinates for layers
    set<int> ys;
    while ((int)ys.size() < L) {
        ys.insert(rnd.next(1, 100));
    }
    vector<int> yvals(ys.begin(), ys.end());

    // Distribute at least one segment per layer
    vector<int> cnt(L, 1);
    int rem = n - L;
    for (int i = 0; i < rem; i++) {
        cnt[rnd.next(0, L-1)]++;
    }

    // Hyper-parameters for widths and gaps
    int W_MAX = rnd.next(5, 20);
    int GAP_MAX = rnd.next(1, 5);
    int baseOrigin = rnd.next(-50, 50);

    vector<tuple<int,int,int>> segs;
    // Generate segments per layer
    for (int i = 0; i < L; i++) {
        int ci = cnt[i];
        if (ci <= 0) continue;
        int layerShift = rnd.next(-10, 10);
        int cursor = baseOrigin + layerShift;
        int y = yvals[i];
        for (int j = 0; j < ci; j++) {
            int width = rnd.next(1, W_MAX);
            int x0 = cursor;
            int x1 = cursor + width;
            segs.emplace_back(x0, x1, y);
            // Move cursor past this segment, ensuring no touching
            cursor = x1 + rnd.next(1, GAP_MAX);
        }
    }

    // Shuffle segments to randomize order
    shuffle(segs.begin(), segs.end());

    // Output
    println(n);
    for (auto &t : segs) {
        int x0, x1, y;
        tie(x0, x1, y) = t;
        println(x0, x1, y);
    }

    return 0;
}
