#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for size
    int N = rnd.next(2, 10);
    int R = rnd.next(1, N);
    // Hyper-parameter t to bias tree shape: chain vs star
    int t = rnd.next(-2, 2);
    // Build a rooted tree with nodes 1..N
    vector<pair<int,int>> edges;
    for (int u = 2; u <= N; ++u) {
        // parent chosen from [1, u-1] with bias t
        int p = rnd.wnext(u-1, t) + 1;
        edges.emplace_back(p, u);
    }
    // Randomly relabel nodes to hide structure
    vector<int> perm(N);
    for (int i = 0; i < N; ++i) perm[i] = i+1;
    shuffle(perm.begin(), perm.end());
    int newR = perm[R-1];
    // Remap edges
    for (auto &e : edges) {
        e.first = perm[e.first - 1];
        e.second = perm[e.second - 1];
    }
    // Shuffle edges order
    shuffle(edges.begin(), edges.end());
    // Queries count
    int Q = rnd.next(1, min(20, N * 2));
    // Hyper-parameter t2 to bias queries toward extremes or uniform
    int t2 = rnd.next(-1, 1);
    vector<int> qs;
    for (int i = 0; i < Q; ++i) {
        int u = rnd.wnext(N, t2) + 1;
        qs.push_back(u);
    }
    // Output
    println(N, newR, Q);
    for (auto &e : edges) println(e.first, e.second);
    for (int u : qs) println(u);
    return 0;
}
