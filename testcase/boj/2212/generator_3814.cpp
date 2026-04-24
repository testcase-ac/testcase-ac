#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of sensors
    int N = rnd.next(1, 10);

    // Number of stations, between 1 and N, with bias
    int tK = rnd.next(-2, 2);
    int K = rnd.wnext(N, tK) + 1;

    // Cluster-based hyper-parameter for sensor positions
    int maxClusters = min(4, N);
    int clustersCount = rnd.next(1, maxClusters);

    // Distribute N sensors into clustersCount clusters
    vector<int> clusterSizes(clustersCount, 1);
    int rem = N - clustersCount;
    for (int i = 0; i < rem; ++i) {
        int idx = rnd.next(0, clustersCount - 1);
        clusterSizes[idx]++;
    }

    // Duplicate probability for extra variety
    double pDup = rnd.next();

    // Generate sensor positions
    vector<int> positions;
    for (int i = 0; i < clustersCount; ++i) {
        int sz = clusterSizes[i];
        int center = rnd.next(-20, 20);
        int spread = rnd.next(0, 10);
        for (int j = 0; j < sz; ++j) {
            if (!positions.empty() && rnd.next() < pDup) {
                // duplicate an existing position
                positions.push_back(rnd.any(positions));
            } else {
                int offset = (spread > 0 ? rnd.next(-spread, spread) : 0);
                positions.push_back(center + offset);
            }
        }
    }

    // Shuffle to avoid sorted order
    shuffle(positions.begin(), positions.end());

    // Output
    println(N);
    println(K);
    println(positions);

    return 0;
}
