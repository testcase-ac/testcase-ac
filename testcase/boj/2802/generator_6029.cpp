#include "testlib.h"
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of crayons
    int N = rnd.next(2, 15);

    // Choose K with varied cases: small, large, or anywhere
    int K;
    double kCase = rnd.next();
    if (kCase < 0.3) {
        K = rnd.next(2, min(N, 5));
    } else if (kCase < 0.6) {
        K = rnd.next(max(2, N/2), N);
    } else {
        K = rnd.next(2, N);
    }

    // Cluster parameters
    int clusterCnt = rnd.next(1, min(5, K));
    vector<array<int,3>> centers(clusterCnt);
    for (int i = 0; i < clusterCnt; i++) {
        centers[i] = { rnd.next(0, 255), rnd.next(0, 255), rnd.next(0, 255) };
    }

    // Probabilities for outliers and duplicates
    double pOutlier = rnd.next(0.0, 1.0);
    double pDup     = rnd.next(0.0, 1.0);

    // Generate points
    vector<array<int,3>> pts;
    pts.reserve(N);
    for (int i = 0; i < N; i++) {
        if (i > 0 && rnd.next() < pDup) {
            // Duplicate a previous point
            pts.push_back(pts[rnd.next(0, (int)pts.size() - 1)]);
        } else if (rnd.next() < pOutlier) {
            // Random outlier
            pts.push_back({ rnd.next(0,255), rnd.next(0,255), rnd.next(0,255) });
        } else {
            // Clustered point around a random center
            auto c = centers[rnd.next(0, clusterCnt - 1)];
            array<int,3> p;
            for (int d = 0; d < 3; d++) {
                int wiggle = rnd.next(0, 20);
                int delta = (wiggle > 0 ? rnd.next(-wiggle, wiggle) : 0);
                int x = c[d] + delta;
                p[d] = max(0, min(255, x));
            }
            pts.push_back(p);
        }
    }

    // Shuffle and output
    shuffle(pts.begin(), pts.end());
    println(N, K);
    for (auto &p : pts) {
        println(p[0], p[1], p[2]);
    }
    return 0;
}
