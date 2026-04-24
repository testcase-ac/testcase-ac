#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of employees and queries
    int N = rnd.next(2, 10);
    int M = rnd.next(1, 20);

    // Hyper-parameter: shape of the tree (chain vs random)
    int chainPct = rnd.next(0, 100);

    // Build parent array for the tree
    vector<int> parent(N + 1);
    parent[1] = 0;  // root has no parent
    if (rnd.next(0, 99) < chainPct) {
        // chain
        for (int i = 2; i <= N; ++i) {
            parent[i] = i - 1;
        }
    } else {
        // random tree
        for (int i = 2; i <= N; ++i) {
            parent[i] = rnd.next(1, i - 1);
        }
    }

    // Initial salaries (large enough to stay positive after updates)
    int minSal = 200, maxSal = 400;
    vector<int> sal(N + 1);
    for (int i = 1; i <= N; ++i) {
        sal[i] = rnd.next(minSal, maxSal);
    }

    // Output N, M
    println(N, M);

    // Output initial salaries and parents
    // For employee 1, only salary
    println(sal[1]);
    for (int i = 2; i <= N; ++i) {
        println(sal[i], parent[i]);
    }

    // Hyper-parameter: ratio of p-queries
    int pPct = rnd.next(0, 100);
    // Hyper-parameter: maximum absolute update
    vector<int> xOpts = {5, 10, 20};
    int xMax = rnd.any(xOpts);

    // Generate queries
    for (int i = 0; i < M; ++i) {
        if (rnd.next(0, 99) < pPct) {
            int a = rnd.next(1, N);
            int x = rnd.next(-xMax, xMax);
            println("p", a, x);
        } else {
            int a = rnd.next(1, N);
            println("u", a);
        }
    }

    return 0;
}
