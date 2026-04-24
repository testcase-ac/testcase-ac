#include "testlib.h"
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // small sizes for hand checking
    int N = rnd.next(1, 10);
    int C = rnd.next(1, N);
    int M = rnd.next(1, 20);

    // generate colors with possible bias
    int tCol = rnd.next(-1, 1);
    vector<int> colors(N);
    for (int i = 0; i < N; i++) {
        colors[i] = rnd.wnext(C, tCol) + 1;
    }

    // generate tree: either chain or random
    double chainP = rnd.next(0.0, 1.0);
    vector<pair<int,int>> edges;
    if (rnd.next() < chainP) {
        // simple chain 1-2-3-...-N
        for (int i = 2; i <= N; i++) {
            edges.emplace_back(i-1, i);
        }
    } else {
        // random tree by parent pointers
        for (int i = 2; i <= N; i++) {
            int p = rnd.next(1, i-1);
            edges.emplace_back(p, i);
        }
    }
    // shuffle edges to remove order bias
    shuffle(edges.begin(), edges.end());

    // generate queries with bias for v and c
    int tV = rnd.next(-1, 1);
    int tC = rnd.next(-1, 1);
    vector<pair<int,int>> queries;
    for (int i = 0; i < M; i++) {
        int v = rnd.wnext(N, tV) + 1;
        int c = rnd.wnext(C, tC) + 1;
        queries.emplace_back(v, c);
    }

    // output
    println(N, M, C);
    println(colors);
    for (auto &e : edges) println(e.first, e.second);
    for (auto &q : queries) println(q.first, q.second);

    return 0;
}
