#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cities
    int N = rnd.next(2, 10);

    // Hyper-parameter: tree shape type
    // 0 = chain, 1 = star, 2 = random attachment
    int treeType = rnd.next(0, 2);
    vector<pair<int,int>> edges;
    if (treeType == 0) {
        // Chain: 1-2-3-...-N
        for (int i = 2; i <= N; i++) {
            edges.emplace_back(i - 1, i);
        }
    } else if (treeType == 1) {
        // Star centered at 1
        for (int i = 2; i <= N; i++) {
            edges.emplace_back(1, i);
        }
    } else {
        // Random attachment: for each new node i, attach to a random existing node [1, i-1]
        for (int i = 2; i <= N; i++) {
            int p = rnd.next(1, i - 1);
            edges.emplace_back(i, p);
        }
    }

    // Optionally shuffle edge order for diversity
    if (rnd.next() < 0.5) {
        shuffle(edges.begin(), edges.end());
    }

    // Output the tree
    println(N);
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    // Number of visits m
    int maxM = min(20, 2 * N);

    // Hyper-parameter: unique visits vs. allowing repeats
    bool uniqueVisits = rnd.next() < 0.3;
    vector<int> visits;
    int M;
    if (uniqueVisits) {
        // at most one visit per city
        int maxUnique = min(20, N);
        M = rnd.next(1, maxUnique);
        vector<int> pool(N);
        for (int i = 0; i < N; i++) pool[i] = i + 1;
        shuffle(pool.begin(), pool.end());
        visits.assign(pool.begin(), pool.begin() + M);
    } else {
        // allow repeats
        M = rnd.next(1, maxM);
        visits.resize(M);
        for (int i = 0; i < M; i++) {
            visits[i] = rnd.next(1, N);
        }
    }

    // Output visits: one per line
    println(M);
    for (int x : visits) {
        println(x);
    }

    return 0;
}
