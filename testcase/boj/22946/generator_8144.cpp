#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Total circles N between 2 and 20
    int N = rnd.next(2, 20);
    // Number of independent chains (root circles) between 1 and min(4, N)
    int K = rnd.next(1, min(4, N));
    // Distribute N circles into K chains, each chain has at least 1 circle
    vector<int> L(K, 1);
    int rem = N - K;
    for (int i = 0; i < K; ++i) {
        if (i < K - 1) {
            int give = rnd.next(0, rem);
            L[i] += give;
            rem -= give;
        } else {
            L[i] += rem;
        }
    }
    // Build chains: each chain is a strictly nested set of concentric circles
    vector<tuple<int,int,int>> circles;
    const int SPACING = 30000;
    const int JITTER = 5000;
    for (int i = 0; i < K; ++i) {
        int t = L[i];
        // Choose root center far apart to avoid any intersection
        int baseX = i * SPACING + rnd.next(-JITTER, JITTER);
        int baseY = rnd.next(-JITTER, JITTER);
        // Root radius at least t so that r0-(t-1) >= 1
        int r0 = rnd.next(t, 10000);
        // Generate concentric nested circles with radii r0, r0-1, ..., r0-(t-1)
        for (int j = 0; j < t; ++j) {
            int r = r0 - j;
            circles.emplace_back(baseX, baseY, r);
        }
    }
    // Shuffle order to increase variability
    if (rnd.next(0, 1)) {
        shuffle(circles.begin(), circles.end());
    }
    // Output
    println(N);
    for (auto &c : circles) {
        int x, y, r;
        tie(x, y, r) = c;
        println(x, y, r);
    }
    return 0;
}
