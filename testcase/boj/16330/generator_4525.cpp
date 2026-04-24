#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes for hand-checkable tests
    int n = rnd.next(1, 10);
    int m = rnd.next(1, 10);

    // Hyper-parameter: choose coordinate bounds small or large
    long long Xmax, Ymax;
    if (rnd.next() < 0.5) {
        Xmax = rnd.any(vector<long long>{10, 100});
        Ymax = rnd.any(vector<long long>{10, 100});
    } else {
        Xmax = rnd.any(vector<long long>{1000, 1000000, 1000000000});
        Ymax = rnd.any(vector<long long>{1000, 1000000, 1000000000});
    }

    // Generate fishermen positions with some clustering at edges or uniform
    vector<long long> a(m);
    for (int i = 0; i < m; i++) {
        double p = rnd.next();
        if (p < 0.4) {
            // Uniform
            a[i] = rnd.next(1LL, Xmax);
        } else if (p < 0.8) {
            // Cluster near left edge
            long long hi = min(10LL, Xmax);
            a[i] = rnd.next(1LL, hi);
        } else {
            // Cluster near right edge
            long long lo = max(1LL, Xmax - 9);
            a[i] = rnd.next(lo, Xmax);
        }
    }

    // Hyper-parameter for clustering fish around fishermen
    double clusterProb = rnd.next();

    // Generate fish coordinates
    vector<pair<long long, long long>> fish;
    for (int i = 0; i < n; i++) {
        long long x, y;
        if (rnd.next() < clusterProb) {
            // Cluster around a random fisherman
            long long f = rnd.any(a);
            long long range = rnd.next(0LL, min(5LL, Xmax - 1));
            long long dx = rnd.next(-range, range);
            x = f + dx;
            x = max(1LL, min(x, Xmax));
            y = rnd.next(1LL, min(5LL, Ymax));
        } else {
            // Uniformly random
            x = rnd.next(1LL, Xmax);
            y = rnd.next(1LL, Ymax);
        }
        fish.emplace_back(x, y);
    }
    shuffle(fish.begin(), fish.end());

    // Determine fishing rod length, clamped to 1e9
    long long maxL = Xmax + Ymax;
    if (maxL > 1000000000LL) maxL = 1000000000LL;
    long long l;
    if (rnd.next() < 0.5) {
        // Small rod
        l = rnd.next(1LL, min(10LL, maxL));
    } else {
        // Anywhere up to maxL
        l = rnd.next(1LL, maxL);
    }

    // Output in the required format
    println(n, m, l);
    for (auto &p : fish) {
        println(p.first, p.second);
    }
    println(a);

    return 0;
}
