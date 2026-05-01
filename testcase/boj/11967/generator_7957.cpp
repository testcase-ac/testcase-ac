#include "testlib.h"
#include <vector>
#include <tuple>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid size N from 2 to 10
    int N = rnd.next(2, 10);
    // Rough maximum switches
    int Mmax = N * N * 2;

    set<tuple<int,int,int,int>> seen;
    vector<tuple<int,int,int,int>> edges;

    // Hyper-parameter 1: a simple chain of switches to ensure reachability
    int max_chain_len = N - 1; // for row/col/diag patterns
    // biased towards shorter chains
    int chain_len = rnd.wnext(max_chain_len + 1, -1); // in [0, max_chain_len]
    int pattern = rnd.next(0, 2);
    for (int i = 1; i <= chain_len; i++) {
        int sx, sy, tx, ty;
        if (pattern == 0) {
            // along first row
            sx = 1; sy = i;
            tx = 1; ty = i + 1;
        } else if (pattern == 1) {
            // along first column
            sx = i; sy = 1;
            tx = i + 1; ty = 1;
        } else {
            // along diagonal
            sx = i; sy = i;
            tx = i + 1; ty = i + 1;
        }
        auto t = make_tuple(sx, sy, tx, ty);
        if (seen.insert(t).second) {
            edges.push_back(t);
        }
    }

    // Hyper-parameter 2: remaining random switches
    int rem_max = Mmax - (int)edges.size();
    if (rem_max > 0) {
        int rem;
        if (rnd.next() < 0.4) {
            // some chance of uniform remainder
            rem = rnd.next(1, rem_max);
        } else {
            // biased towards larger remainders
            rem = rnd.wnext(rem_max + 1, 1);
        }
        rem = min(rem, rem_max);
        while (rem > 0) {
            int sx = rnd.next(1, N), sy = rnd.next(1, N);
            int tx = rnd.next(1, N), ty = rnd.next(1, N);
            auto t = make_tuple(sx, sy, tx, ty);
            if (seen.insert(t).second) {
                edges.push_back(t);
                rem--;
            }
        }
    }

    // Ensure at least one switch (M >= 1)
    if (edges.empty()) {
        while (true) {
            int sx = rnd.next(1, N), sy = rnd.next(1, N);
            int tx = rnd.next(1, N), ty = rnd.next(1, N);
            auto t = make_tuple(sx, sy, tx, ty);
            if (seen.insert(t).second) {
                edges.push_back(t);
                break;
            }
        }
    }

    // Shuffle to mix chain and random
    shuffle(edges.begin(), edges.end());

    // Output
    int M = edges.size();
    println(N, M);
    for (auto &e : edges) {
        println(get<0>(e), get<1>(e), get<2>(e), get<3>(e));
    }

    return 0;
}
