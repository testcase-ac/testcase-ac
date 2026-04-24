#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose number of nodes between 2 and 10
    int N = rnd.next(2, 10);

    // Hyper-parameter: choose tree shape
    // 0 = chain, 1 = star, 2 = random parent tree
    int treeType = rnd.next(0, 2);

    vector<pair<int,int>> edges;
    if (treeType == 0) {
        // chain 1-2-3-...-N
        for (int i = 1; i < N; ++i)
            edges.emplace_back(i, i + 1);
    } else if (treeType == 1) {
        // star around a random center
        int center = rnd.next(1, N);
        for (int i = 1; i <= N; ++i)
            if (i != center)
                edges.emplace_back(center, i);
    } else {
        // random parent for each new node
        for (int i = 2; i <= N; ++i) {
            int p = rnd.next(1, i - 1);
            edges.emplace_back(p, i);
        }
    }

    // Shuffle edge list to vary order
    shuffle(edges.begin(), edges.end());

    // Permutation of node labels for extra randomness
    vector<int> perm(N + 1);
    for (int i = 1; i <= N; ++i) perm[i] = i;
    shuffle(perm.begin() + 1, perm.end());

    for (auto &e : edges) {
        e.first = perm[e.first];
        e.second = perm[e.second];
    }

    // Final shuffle
    shuffle(edges.begin(), edges.end());

    // Output
    println(N);
    for (auto &e : edges)
        println(e.first, e.second);

    return 0;
}
