#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of buildings
    int N = rnd.next(1, 10);

    // Hyper-parameter for maximum build time
    vector<int> possibleMaxTime = {10, 100, 1000, 100000};
    int maxTime = rnd.any(possibleMaxTime);

    // Hyper-parameter for dependency density
    vector<double> possibleDepProbs = {0.0, 0.2, 0.5, 0.8, 1.0};
    double depProb = rnd.any(possibleDepProbs);

    // Should we shuffle building IDs?
    bool shuffleIDs = rnd.next(0, 1);
    // Should we shuffle the order of dependencies per building?
    bool shuffleDepsOrder = rnd.next(0, 1);

    // Prepare a topological order and possibly shuffle it for ID assignment
    vector<int> P(N);
    iota(P.begin(), P.end(), 1);
    if (shuffleIDs) {
        shuffle(P.begin(), P.end());
    }

    // For each topo-position k, assign a build time and pick dependencies among [0..k-1]
    vector<int> times(N);
    vector<vector<int>> prereqsRaw(N);
    for (int k = 0; k < N; ++k) {
        times[k] = rnd.next(1, maxTime);
        if (k > 0) {
            for (int j = 0; j < k; ++j) {
                if (rnd.next() < depProb) {
                    prereqsRaw[k].push_back(j);
                }
            }
            if (shuffleDepsOrder) {
                shuffle(prereqsRaw[k].begin(), prereqsRaw[k].end());
            }
        }
    }

    // Map from building ID to its time and dependency list
    vector<int> timesByID(N+1);
    vector<vector<int>> depsByID(N+1);
    for (int k = 0; k < N; ++k) {
        int id = P[k];
        timesByID[id] = times[k];
        for (int j : prereqsRaw[k]) {
            depsByID[id].push_back(P[j]);
        }
    }

    // Output
    printf("%d\n", N);
    for (int id = 1; id <= N; ++id) {
        // time then dependencies then -1
        printf("%d", timesByID[id]);
        for (int d : depsByID[id]) {
            printf(" %d", d);
        }
        printf(" -1\n");
    }
    return 0;
}
