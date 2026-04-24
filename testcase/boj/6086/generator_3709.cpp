#include "testlib.h"
#include <vector>
#include <tuple>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of extra nodes besides 'A' and 'Z'
    int K = rnd.wnext(7, -1); // biased small, in [0..6]
    // Build pool of possible node labels excluding 'A' and 'Z'
    string alpha;
    for (char c = 'A'; c <= 'Z'; ++c) if (c != 'A' && c != 'Z') alpha.push_back(c);
    for (char c = 'a'; c <= 'z'; ++c) if (c != 'A' && c != 'Z') alpha.push_back(c);
    shuffle(alpha.begin(), alpha.end());
    vector<char> nodes;
    nodes.push_back('A');
    nodes.push_back('Z');
    for (int i = 0; i < K && i < (int)alpha.size(); ++i)
        nodes.push_back(alpha[i]);

    int base = nodes.size();
    // Hyper-parameter: number of edges M
    int M;
    if (rnd.next() < 0.7) {
        M = rnd.next(2, base);
    } else {
        M = rnd.next(base, min(18, base * 3));
    }

    vector< tuple<char,char,int> > edges;
    edges.reserve(M + 2);

    // Generate random edges
    for (int i = 0; i < M; ++i) {
        char u, v;
        do {
            u = rnd.any(nodes);
            v = rnd.any(nodes);
        } while (u == v);
        int cap = (rnd.next() < 0.5 ? rnd.next(1, 10) : rnd.next(50, 1000));
        edges.emplace_back(u, v, cap);
    }

    // Ensure at least one edge incident to 'A'
    bool hasA = false, hasZ = false;
    for (auto &e : edges) {
        char u = get<0>(e), v = get<1>(e);
        if (u == 'A' || v == 'A') hasA = true;
        if (u == 'Z' || v == 'Z') hasZ = true;
    }
    if (!hasA && !edges.empty()) {
        // replace endpoints of first edge to include A
        char other;
        do { other = rnd.any(nodes); } while (other == 'A');
        get<0>(edges[0]) = 'A';
        get<1>(edges[0]) = other;
    }
    if (!hasZ && (int)edges.size() > 1) {
        char other;
        do { other = rnd.any(nodes); } while (other == 'Z');
        get<0>(edges[1]) = other;
        get<1>(edges[1]) = 'Z';
    }

    // Sometimes add a direct edge A-Z
    if (rnd.next() < 0.3) {
        int cap = (rnd.next() < 0.5 ? rnd.next(1, 10) : rnd.next(50, 1000));
        edges.emplace_back('A', 'Z', cap);
    }

    // Final shuffle of edge order
    shuffle(edges.begin(), edges.end());

    // Output
    int N = edges.size();
    println(N);
    for (auto &e : edges) {
        println(get<0>(e), get<1>(e), get<2>(e));
    }
    return 0;
}
