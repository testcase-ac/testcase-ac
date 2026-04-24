#include "testlib.h"
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    // Randomly pick which distribution we use.
    bool smallDistribution = (rnd.next(2) == 0);

    int N;
    int maxBudget;

    if (smallDistribution) {
        // Verifiability distribution: very small N, small budgets
        N = rnd.next(3, 5);
        maxBudget = 10;
    } else {
        // Variability distribution: slightly larger N, bigger budgets
        N = rnd.next(6, 10);
        maxBudget = 100;
    }

    // Print N
    cout << N << "\n";

    // Generate and print the budget requests
    vector<long long> budgets(N);
    long long sumBudgets = 0;
    for (int i = 0; i < N; i++) {
        budgets[i] = rnd.next(1, maxBudget);
        sumBudgets += budgets[i];
    }

    for (int i = 0; i < N; i++) {
        cout << budgets[i] << (i + 1 == N ? '\n' : ' ');
    }

    // Generate and print the total budget M
    // Range: [N, 2 * sumBudgets] to allow either partial or full funding
    long long M = rnd.next((long long)N, 2LL * sumBudgets);
    cout << M << "\n";

    return 0;
}
