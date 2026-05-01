#include "testlib.h"
using namespace std;

struct Edge {
    int a, b;
    long long c;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide N
    double pN = rnd.next(0.0, 1.0);
    int N;
    if (pN < 0.3)
        N = rnd.next(1, 5);
    else if (pN < 0.8)
        N = rnd.next(6, 12);
    else
        N = rnd.next(13, 20);

    vector<Edge> edges;

    if (N > 1) {
        int treeType = rnd.next(0, 3); // 0: path, 1: star, 2: random, 3: binary

        if (treeType == 0) {
            // Path: 1-2-3-...-N
            for (int i = 1; i < N; i++) {
                Edge e;
                e.a = i;
                e.b = i + 1;
                e.c = 0;
                edges.push_back(e);
            }
        } else if (treeType == 1) {
            // Star
            int center = rnd.next(1, N);
            for (int v = 1; v <= N; v++) {
                if (v == center) continue;
                Edge e;
                e.a = center;
                e.b = v;
                e.c = 0;
                edges.push_back(e);
            }
        } else if (treeType == 2) {
            // Random tree via growing
            for (int v = 2; v <= N; v++) {
                int u = rnd.next(1, v - 1);
                Edge e;
                e.a = u;
                e.b = v;
                e.c = 0;
                edges.push_back(e);
            }
        } else {
            // Binary-like tree: parent = i/2
            for (int v = 2; v <= N; v++) {
                int u = v / 2;
                Edge e;
                e.a = u;
                e.b = v;
                e.c = 0;
                edges.push_back(e);
            }
        }

        // Assign weights
        int weightType = rnd.next(0, 3); // 0: all 1, 1: small random, 2: mix small/big, 3: increasing
        for (int i = 0; i < (int)edges.size(); i++) {
            long long w;
            if (weightType == 0) {
                w = 1;
            } else if (weightType == 1) {
                w = rnd.next(1, 10);
            } else if (weightType == 2) {
                if (rnd.next(0, 1) == 0) w = 1;
                else w = 1000000000LL;
            } else {
                w = i + 1;
            }
            edges[i].c = w;
        }

        // Randomly swap endpoints and shuffle order
        for (int i = 0; i < (int)edges.size(); i++) {
            if (rnd.next(0, 1) == 1) {
                swap(edges[i].a, edges[i].b);
            }
        }
        shuffle(edges.begin(), edges.end());
    }

    // Decide Q
    int Q;
    if (N == 1) {
        Q = rnd.next(1, 5);
    } else {
        int maxQ = min(25, max(3, 2 * N));
        Q = rnd.next(1, maxQ);
    }

    // Output N and Q
    println(N, Q);

    // Output edges
    for (int i = 0; i < (int)edges.size(); i++) {
        println(edges[i].a, edges[i].b, edges[i].c);
    }

    // Generate queries
    vector<pair<int,int> > queries;

    if (N == 1) {
        // Only possible query is [1,1]
        for (int i = 0; i < Q; i++) {
            println(1, 1);
        }
        return 0;
    }

    // Some structured queries
    if ((int)queries.size() < Q) queries.push_back(make_pair(1, N)); // full range
    if ((int)queries.size() < Q) queries.push_back(make_pair(1, 1)); // first
    if ((int)queries.size() < Q) queries.push_back(make_pair(N, N)); // last
    if (N >= 2 && (int)queries.size() < Q) {
        int pos = rnd.next(1, N - 1);
        queries.push_back(make_pair(pos, pos + 1)); // adjacent pair
    }
    if ((int)queries.size() < Q) {
        int len = max(1, N / 2);
        int l = rnd.next(1, N - len + 1);
        int r = l + len - 1;
        queries.push_back(make_pair(l, r)); // mid-sized interval
    }

    // Fill remaining with random intervals, biased towards singles sometimes
    while ((int)queries.size() < Q) {
        if (rnd.next(0.0, 1.0) < 0.3) {
            int x = rnd.next(1, N);
            queries.push_back(make_pair(x, x));
        } else {
            int len = rnd.next(1, N);
            int l = rnd.next(1, N - len + 1);
            int r = l + len - 1;
            queries.push_back(make_pair(l, r));
        }
    }

    // Output queries
    for (int i = 0; i < Q; i++) {
        println(queries[i].first, queries[i].second);
    }

    return 0;
}
