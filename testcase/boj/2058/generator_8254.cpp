#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of energy states
    int N = rnd.next(2, 15);
    // Build a random tree with edge weights as distinct powers of two
    vector<int> parent(N+1), w(N+1);
    for (int v = 2; v <= N; v++) {
        parent[v] = rnd.next(1, v-1);
        w[v] = 1 << (v-2);  // weights: 1,2,4,...
    }
    // Assign energies as cumulative sums, starting from a small random base
    int base = rnd.next(1, 10);
    vector<int> A(N+1);
    A[1] = base;
    for (int v = 2; v <= N; v++) {
        A[v] = A[parent[v]] + w[v];
    }
    // Proton energies include exactly the edge weights
    vector<int> P;
    for (int v = 2; v <= N; v++) {
        P.push_back(w[v]);
    }
    int max_edge = *max_element(P.begin(), P.end());
    // Add a few extra proton energies that don't match any actual edge diff
    int extra = rnd.next(0, 3);
    set<int> used(P.begin(), P.end());
    for (int i = 0; i < extra; i++) {
        int x;
        do {
            x = rnd.next(max_edge + 1, max_edge + 100);
        } while (used.count(x));
        used.insert(x);
        P.push_back(x);
    }
    int M = P.size();
    // Shuffle the order for variability
    vector<int> energies(A.begin() + 1, A.end());
    shuffle(energies.begin(), energies.end());
    shuffle(P.begin(), P.end());
    // Output
    println(N, M);
    for (int x : energies) println(x);
    for (int x : P) println(x);
    return 0;
}
