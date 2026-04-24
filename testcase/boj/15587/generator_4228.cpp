#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small size
    int N = rnd.next(2, 10);
    vector<pair<int,int>> edges;
    // Choose a tree shape hyper-parameter
    int style = rnd.next(0, 3);
    if (style == 0) {
        // random tree by connecting each new node to a previous one
        for (int i = 2; i <= N; i++) {
            int j = rnd.next(1, i - 1);
            edges.emplace_back(i, j);
        }
    } else if (style == 1) {
        // chain
        for (int i = 1; i < N; i++)
            edges.emplace_back(i, i + 1);
    } else if (style == 2) {
        // star
        int center = rnd.next(1, N);
        for (int i = 1; i <= N; i++)
            if (i != center)
                edges.emplace_back(center, i);
    } else {
        // balanced binary-ish tree: parent = i/2
        for (int i = 2; i <= N; i++) {
            int p = i / 2;
            if (p < 1) p = 1;
            edges.emplace_back(i, p);
        }
    }
    // Shuffle edge order
    shuffle(edges.begin(), edges.end());
    // Determine degrees to find leaves/internal
    vector<int> deg(N+1, 0);
    for (auto &e : edges) {
        deg[e.first]++;
        deg[e.second]++;
    }
    vector<int> leaves, internal;
    for (int i = 1; i <= N; i++) {
        if (deg[i] == 1) leaves.push_back(i);
        else internal.push_back(i);
    }
    // Choose K: sometimes a leaf, sometimes internal
    int K;
    if (!leaves.empty() && rnd.next() < 0.5) {
        K = rnd.any(leaves);
    } else if (!internal.empty()) {
        K = rnd.any(internal);
    } else {
        K = rnd.any(leaves);
    }
    // Output
    println(N, K);
    for (auto &e : edges)
        println(e.first, e.second);
    return 0;
}
