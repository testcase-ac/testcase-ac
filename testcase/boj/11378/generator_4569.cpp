#include "testlib.h"
#include <numeric>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small sizes for hand-checkability
    int N = rnd.next(2, 10);
    int M = rnd.next(1, 10);
    int K = rnd.next(1, N);

    // Hyper-parameters for diversity
    double overallDensity = rnd.next(0.0, 1.0);   // chance to use weighted vs uniform
    int globalExp = rnd.next(-2, 2);              // exponent for wnext
    double singleProb = rnd.next(0.0, 1.0);       // chance for single-task employee
    bool enforceAll = rnd.next() < 0.3;           // chance to have a "super" employee
    int superEmp = enforceAll ? rnd.next(1, N) : -1;

    // Prepare tasks 1..M
    vector<int> baseTasks(M);
    iota(baseTasks.begin(), baseTasks.end(), 1);

    // Output header
    println(N, M, K);

    for (int i = 1; i <= N; i++) {
        // Determine this employee's task list
        vector<int> avail = baseTasks;
        int d;
        if (enforceAll && i == superEmp) {
            // Super employee can do all tasks
            d = M;
        } else if (rnd.next() < singleProb * 0.3) {
            // Some employees can do exactly one random task
            d = 1;
        } else {
            // Mix uniform and weighted degree
            if (rnd.next() < overallDensity) {
                // weighted: more skewed distributions
                d = rnd.wnext(M + 1, globalExp);
            } else {
                // uniform
                d = rnd.next(0, M);
            }
        }
        // Shuffle and pick first d tasks
        shuffle(avail.begin(), avail.end());
        if (d > M) d = M;
        // Print this employee's line
        printf("%d", d);
        for (int j = 0; j < d; j++) {
            printf(" %d", avail[j]);
        }
        printf("\n");
    }

    return 0;
}
