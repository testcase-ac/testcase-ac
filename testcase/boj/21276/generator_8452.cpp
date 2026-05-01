#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose scenario mode for variability
    int mode = rnd.next(0, 4);

    int N;
    if (mode == 0) {
        N = 1; // single person, no ancestors
    } else if (mode == 1) {
        N = rnd.next(2, 5); // small chain
    } else if (mode == 2) {
        N = rnd.next(2, 7); // star-like
    } else if (mode == 3) {
        N = rnd.next(2, 10); // random forest, smaller
    } else {
        N = rnd.next(5, 10); // random forest with a bit more nodes
    }

    // Generate simple, readable names: "a", "b", "c", ...
    vector<string> names(N);
    for (int i = 0; i < N; ++i) {
        names[i] = string(1, char('a' + i));
    }

    // Build a forest (each family is a rooted tree)
    vector<int> parent(N, -1); // -1 means root

    if (N > 1) {
        vector<int> all(N);
        for (int i = 0; i < N; ++i) all[i] = i;
        shuffle(all.begin(), all.end());

        if (mode == 1) {
            // Chain: one long line
            int root = all[0];
            parent[root] = -1;
            for (int i = 1; i < N; ++i) {
                parent[all[i]] = all[i - 1];
            }
        } else if (mode == 2) {
            // Star: one root, all others are direct children
            int root = all[0];
            parent[root] = -1;
            for (int i = 1; i < N; ++i) {
                parent[all[i]] = root;
            }
        } else {
            // Random forest: 1..K families, each tree random
            int maxK = (mode == 3 ? 2 : 3);
            if (maxK > N) maxK = N;
            int K = rnd.next(1, maxK);

            // Assign sizes to each family (at least 1 per family)
            vector<int> sizes(K, 1);
            int remaining = N - K;
            for (int i = 0; i < remaining; ++i) {
                int f = rnd.next(0, K - 1);
                sizes[f]++;
            }

            int idx = 0;
            for (int f = 0; f < K; ++f) {
                vector<int> fam;
                for (int c = 0; c < sizes[f]; ++c) {
                    fam.push_back(all[idx++]);
                }
                // Build a random tree within this family
                int root = fam[0];
                parent[root] = -1;
                for (int j = 1; j < (int)fam.size(); ++j) {
                    int v = fam[j];
                    int parIdx = rnd.next(0, j - 1);
                    parent[v] = fam[parIdx];
                }
            }
        }
    }

    // Collect all ancestor pairs (X, Y): Y is an ancestor of X
    // This is the full transitive closure, as required by the problem.
    vector<pair<int,int>> anc;
    for (int i = 0; i < N; ++i) {
        int cur = parent[i];
        while (cur != -1) {
            anc.push_back({i, cur});
            cur = parent[cur];
        }
    }

    // Use all remembered relations (complete ancestor information)
    int M = (int)anc.size();
    shuffle(anc.begin(), anc.end());

    // Randomize order of given names in the second line for variability
    vector<string> inputOrder = names;
    if (rnd.next(0, 1) == 1) {
        shuffle(inputOrder.begin(), inputOrder.end());
    }

    // Output
    println(N);
    println(inputOrder);
    println(M);
    for (auto &p : anc) {
        int x = p.first;  // descendant
        int y = p.second; // ancestor
        println(names[x], names[y]);
    }

    return 0;
}
