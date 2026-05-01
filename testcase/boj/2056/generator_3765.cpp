#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of tasks
    int N = rnd.next(3, 10);
    // Maximum processing time
    int tmax = rnd.next(10, 100);
    // Density of prerequisite relations
    double density = rnd.next(0.0, 1.0);

    // Times and dependency lists
    vector<int> tim(N+1);
    vector<vector<int>> deps(N+1);

    // Assign random times
    for (int i = 1; i <= N; i++) {
        tim[i] = rnd.next(1, tmax);
    }

    // Generate dependencies: only from lower-numbered tasks
    for (int k = 2; k <= N; k++) {
        for (int i = 1; i < k; i++) {
            if (rnd.next() < density) {
                deps[k].push_back(i);
            }
        }
        // Randomize the order of prerequisites
        shuffle(deps[k].begin(), deps[k].end());
    }

    // Output format
    println(N);
    for (int k = 1; k <= N; k++) {
        printf("%d %d", tim[k], (int)deps[k].size());
        for (int x : deps[k]) {
            printf(" %d", x);
        }
        printf("\n");
    }

    return 0;
}
