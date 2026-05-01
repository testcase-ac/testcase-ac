#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of towns and universes
    int N = rnd.next(2, 12);
    int O = rnd.next(1, 6);
    int S = rnd.next(1, N);
    int E;
    do {
        E = rnd.next(1, N);
    } while (E == S);

    // Generate road candidates
    vector<pair<int,int>> e_pool;
    for (int i = 1; i <= N; ++i)
        for (int j = i + 1; j <= N; ++j)
            e_pool.emplace_back(i, j);
    shuffle(e_pool.begin(), e_pool.end());

    // Choose number of roads M (at least 1, capped for readability)
    int Mcap = min((int)e_pool.size(), 2 * N + rnd.next(0, N));
    int M = rnd.next(1, Mcap);
    vector<pair<int,int>> edges(e_pool.begin(), e_pool.begin() + M);

    // Generate wormhole candidates
    vector<pair<int,int>> wh_pool;
    if (O > 1) {
        for (int w = 1; w <= O - 1; ++w)
            for (int x = 1; x <= N; ++x)
                wh_pool.emplace_back(w, x);
        shuffle(wh_pool.begin(), wh_pool.end());
    }

    // Choose number of wormholes P
    int P = 0;
    if (O > 1) {
        int Pcap = min((int)wh_pool.size(), 2 * N);
        P = rnd.next(1, Pcap);
    }
    vector<pair<int,int>> whs(wh_pool.begin(), wh_pool.begin() + P);

    // Build queries with some fixed edge cases and some random ones
    vector<pair<int,int>> qs;
    qs.emplace_back(0, 0);
    qs.emplace_back(100, 0);
    qs.emplace_back(0, 100);
    qs.emplace_back(100, 100);
    int extra = rnd.next(0, 4);
    for (int i = 0; i < extra; ++i) {
        int a = rnd.next(0, 100);
        int b = rnd.next(0, 100);
        qs.emplace_back(a, b);
    }
    shuffle(qs.begin(), qs.end());

    // Output the test case
    println(N, O, S, E);
    println(M);
    for (auto &e : edges)
        println(e.first, e.second);
    println(P);
    for (auto &w : whs)
        println(w.first, w.second);
    println((int)qs.size());
    for (auto &q : qs)
        println(q.first, q.second);

    return 0;
}
