#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of employees
    int N = rnd.next(1, 15);

    // Generate a random root
    int root = rnd.next(1, N);

    // Create a random permutation of employee labels
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);
    shuffle(perm.begin(), perm.end());
    // Ensure the chosen root is at position 0
    for (int i = 1; i < N; i++) {
        if (perm[i] == root) {
            swap(perm[0], perm[i]);
            break;
        }
    }

    // Parent array, 1-based
    vector<int> parent(N+1, -1);
    parent[root] = -1;

    // Choose a tree structure type for variability
    // 0: skewed random (weighted attachment)
    // 1: simple chain
    // 2: complete binary tree shape
    // 3: star
    int structType = rnd.next(0, 3);

    if (structType == 0) {
        // Skewed random tree using weighted next
        int t = rnd.next(-3, 3);
        for (int j = 1; j < N; j++) {
            // Attach perm[j] to one of perm[0..j-1]
            int k = rnd.wnext(j, t); // gives [0, j-1] skewed by t
            parent[perm[j]] = perm[k];
        }
    } else if (structType == 1) {
        // Chain: each node attaches to the previous in perm order
        for (int j = 1; j < N; j++) {
            parent[perm[j]] = perm[j-1];
        }
    } else if (structType == 2) {
        // Complete binary tree shape over perm order
        for (int j = 1; j < N; j++) {
            parent[perm[j]] = perm[(j-1)/2];
        }
    } else {
        // Star: all nodes attach to the root
        for (int j = 1; j < N; j++) {
            parent[perm[j]] = perm[0];
        }
    }

    // Output
    println(N);
    for (int i = 1; i <= N; i++) {
        println(parent[i]);
    }

    return 0;
}
