#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: bias towards small/large via wnext
    int biasN = rnd.next(-1, 1);
    int N = rnd.wnext(9, biasN) + 2; // N in [2,10]

    // Hyper-parameter for maximum weight
    int biasW = rnd.next(-1, 1);
    int maxW = rnd.next(1, 100);

    // Hyper-parameter for extra edges probability
    int p10 = rnd.next(1, 9);
    double extraP = p10 / 10.0;

    // Initialize adjacency matrix with zeros (0 means no edge or self-loop)
    vector<vector<int>> W(N, vector<int>(N, 0));

    // Ensure at least one Hamiltonian cycle exists
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin(), perm.end());
    for (int i = 0; i < N; i++) {
        int u = perm[i];
        int v = perm[(i + 1) % N];
        W[u][v] = rnd.next(1, maxW);
    }

    // Fill other edges randomly with probability extraP
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j || W[i][j] > 0) continue;
            if (rnd.next() < extraP) {
                W[i][j] = rnd.wnext(maxW, biasW);
            }
        }
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        println(W[i]);
    }

    return 0;
}
