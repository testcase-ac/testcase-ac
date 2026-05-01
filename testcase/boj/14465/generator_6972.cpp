#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with variability: sometimes small, sometimes medium
    int tN = rnd.next(-2, 2);
    int N = rnd.wnext(30, tN) + 1; // N in [1..30], skewed by tN

    // Choose K and B with light bias
    int tK = rnd.next(-1, 1);
    int K = rnd.wnext(N, tK) + 1;  // K in [1..N]
    int tB = rnd.next(-1, 1);
    int B = rnd.wnext(N, tB) + 1;  // B in [1..N]

    vector<int> broken;
    double clusterProb = rnd.next(0.0, 1.0);

    if (B >= 2 && clusterProb < 0.3) {
        // generate a cluster of broken signals
        int clusterSize = rnd.next(1, B);
        int start = rnd.next(1, max(1, N - clusterSize + 1));
        // add the cluster
        for (int i = 0; i < clusterSize; i++)
            broken.push_back(start + i);
        // fill the rest uniformly
        vector<int> rest;
        rest.reserve(N - clusterSize);
        for (int i = 1; i <= N; i++)
            if (i < start || i >= start + clusterSize)
                rest.push_back(i);
        shuffle(rest.begin(), rest.end());
        for (int i = 0; (int)broken.size() < B; i++)
            broken.push_back(rest[i]);
    } else {
        // uniform random broken positions
        broken.reserve(N);
        for (int i = 1; i <= N; i++)
            broken.push_back(i);
        shuffle(broken.begin(), broken.end());
        broken.resize(B);
    }

    // Shuffle the broken list to output in arbitrary order
    shuffle(broken.begin(), broken.end());

    // Output the test case
    println(N, K, B);
    for (int x : broken)
        println(x);

    return 0;
}
