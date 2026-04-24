#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of knob distances
    int N = rnd.next(1, 10);
    // Upper bound for distances, ensure at least N distinct values available
    int maxK = rnd.next(N, 20);

    // Generate N distinct shoot distances from [1..maxK]
    vector<int> poolK(maxK);
    iota(poolK.begin(), poolK.end(), 1);
    shuffle(poolK.begin(), poolK.end());
    vector<int> K(poolK.begin(), poolK.begin() + N);
    sort(K.begin(), K.end());

    // Compute reachable distances in <=2 strokes
    set<int> reach;
    for (int k : K) {
        reach.insert(k);
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            reach.insert(K[i] + K[j]);
        }
    }
    vector<int> reachVec(reach.begin(), reach.end());

    // Number of holes
    int M = rnd.next(1, 20);
    // Probability to pick a reachable hole
    double pReach = rnd.next();

    // Build list of unreachable distances in [1..2*maxK]
    vector<int> unreachable;
    int maxD = 2 * maxK;
    for (int d = 1; d <= maxD; ++d) {
        if (!reach.count(d)) unreachable.push_back(d);
    }

    // Generate hole distances
    vector<int> holes;
    holes.reserve(M);
    for (int i = 0; i < M; ++i) {
        if (!reachVec.empty() && rnd.next() < pReach) {
            // pick a reachable distance
            holes.push_back(rnd.any(reachVec));
        } else if (!unreachable.empty()) {
            // pick an unreachable distance
            holes.push_back(rnd.any(unreachable));
        } else {
            // fallback if everything is reachable
            holes.push_back(rnd.any(reachVec));
        }
    }

    // Output in the required format
    println(N);
    for (int k : K) println(k);
    println(M);
    for (int d : holes) println(d);

    return 0;
}
