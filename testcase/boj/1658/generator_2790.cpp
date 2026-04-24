#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of pens and customers
    int M = rnd.next(1, 10);
    int N = rnd.next(1, 10);

    // Hyper-parameter: density of non-empty pens and max pigs per pen
    double pNonzero = rnd.next();
    int maxPig = rnd.next(1, 20);

    // Generate initial pigs in each pen
    vector<int> pigs(M);
    for (int i = 0; i < M; i++) {
        if (rnd.next() < pNonzero)
            pigs[i] = rnd.next(1, maxPig);
        else
            pigs[i] = 0;
    }

    // Compute total initial pigs
    int initSum = accumulate(pigs.begin(), pigs.end(), 0);

    // Hyper-parameter: demand factor
    vector<int> factors = {1, 2, 3};
    int demandFactor = rnd.any(factors);
    int maxDemand = initSum * demandFactor;

    // Output M, N and initial pigs
    println(M, N);
    println(pigs);

    // For each customer, choose a random subset of keys and a demand B
    for (int i = 0; i < N; i++) {
        double keyDensity = rnd.next();
        vector<int> keys;
        for (int j = 1; j <= M; j++) {
            if (rnd.next() < keyDensity)
                keys.push_back(j);
        }
        int A = keys.size();
        int B = (maxDemand > 0 ? rnd.next(0, maxDemand) : 0);

        // Print customer line: A, keys..., B
        printf("%d", A);
        for (int k : keys)
            printf(" %d", k);
        printf(" %d\n", B);
    }

    return 0;
}
