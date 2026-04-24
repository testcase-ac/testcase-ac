#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small sizes
    int N = rnd.next(1, 10);

    // Hyper-parameter: tree shape
    int shape = rnd.next(0, 2); // 0=random, 1=chain, 2=star
    vector<pair<int,int>> edges;
    if (N > 1) {
        if (shape == 0) {
            // random parent for each node 2..N
            for (int v = 2; v <= N; ++v) {
                int p = rnd.next(1, v - 1);
                edges.emplace_back(p, v);
            }
        } else if (shape == 1) {
            // chain 1-2-3-...-N
            for (int i = 1; i < N; ++i)
                edges.emplace_back(i, i + 1);
        } else {
            // star
            int center = rnd.next(1, N);
            for (int i = 1; i <= N; ++i)
                if (i != center)
                    edges.emplace_back(center, i);
        }
        shuffle(edges.begin(), edges.end());
    }

    // Initial fruit sizes with a skew hyper-parameter
    vector<int> xi(N);
    for (int i = 0; i < N; ++i) {
        bool small = rnd.next(0, 1) == 0;
        int t = small ? -1 : 1;
        xi[i] = rnd.wnext(20, t) + 1; // in [1..21], roughly
    }

    // Queries
    int Q = rnd.next(1, 20);
    double pType2 = rnd.next(0.1, 0.6); // probability of type-2
    vector<vector<long long>> qs;
    int cnt2 = 0;
    for (int i = 0; i < Q; ++i) {
        if (rnd.next() < pType2) {
            int u = rnd.next(1, N);
            qs.push_back({2, u});
            cnt2++;
        } else {
            int u = rnd.next(1, N);
            // amount of water, skewed
            bool small = rnd.next(0, 1) == 0;
            int t = small ? -1 : 1;
            long long x = rnd.wnext(20, t) + 1;
            qs.push_back({1, u, x});
        }
    }
    // ensure at least one type-2
    if (cnt2 == 0) {
        int u = rnd.next(1, N);
        qs.back() = {2, u};
    }
    shuffle(qs.begin(), qs.end());

    // Output
    println(N, Q);
    for (auto &e : edges)
        println(e.first, e.second);
    println(xi);
    for (auto &v : qs) {
        if (v[0] == 1)
            println(1, v[1], v[2]);
        else
            println(2, v[1]);
    }
    return 0;
}
