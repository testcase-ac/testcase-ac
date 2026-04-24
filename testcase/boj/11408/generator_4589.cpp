#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of workers and jobs
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);

    // Maximum cost hyper-parameter
    int maxCost = rnd.next(0, 20);

    // Output N and M
    println(N, M);

    // For each worker generate a random subset of jobs with costs
    for (int i = 0; i < N; i++) {
        // Bias the number of options per worker towards small or large
        int bias = rnd.next(-2, 2);
        int k = rnd.wnext(M + 1, bias); // yields 0..M

        // Sample k distinct jobs
        vector<int> jobs(M);
        iota(jobs.begin(), jobs.end(), 1);
        shuffle(jobs.begin(), jobs.end());
        jobs.resize(k);

        // Randomly decide whether to sort the job IDs (diversity)
        if (rnd.next(0, 1)) {
            sort(jobs.begin(), jobs.end());
        }

        // Print the count and each (job, cost) pair
        printf("%d", k);
        for (int j : jobs) {
            int c = rnd.next(0, maxCost);
            printf(" %d %d", j, c);
        }
        printf("\n");
    }

    return 0;
}
