#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of fighters (at least 3 to allow an odd cycle)
    int N = rnd.next(3, 10);

    // Prepare a random permutation of fighter IDs
    vector<int> fighters(N);
    iota(fighters.begin(), fighters.end(), 1);
    shuffle(fighters.begin(), fighters.end());

    // Choose an odd cycle length c ∈ {3,5,7,9} ∩ [3,N]
    vector<int> oddLens;
    for (int len = 3; len <= N; len += 2)
        oddLens.push_back(len);
    int c = rnd.any(oddLens);

    // Pick c distinct nodes for the odd cycle
    vector<int> cycle_nodes(fighters.begin(), fighters.begin() + c);
    // Hyperparam: maybe reverse the cycle order
    if (rnd.next(0, 1))
        reverse(cycle_nodes.begin(), cycle_nodes.end());

    // Hyperparam: probability of swapping endpoints of each fight
    double swapEdgeProb = rnd.next();

    // Build the fights list: first an odd cycle of length c
    vector<pair<int,int>> fights;
    fights.reserve(c + N + 5);

    // Path edges of the cycle
    for (int i = 0; i < c - 1; i++) {
        int u = cycle_nodes[i], v = cycle_nodes[i + 1];
        if (rnd.next() < swapEdgeProb) swap(u, v);
        fights.emplace_back(u, v);
    }
    // Closing edge to form the odd cycle
    {
        int u = cycle_nodes[c - 1], v = cycle_nodes[0];
        if (rnd.next() < swapEdgeProb) swap(u, v);
        fights.emplace_back(u, v);
    }

    // Decide number of extra fights using a weighted sampler
    vector<int> tvals = { -2, -1, 0, 1, 2 };
    int t = rnd.any(tvals);
    int extra = rnd.wnext(N + 1, t);

    // Append extra fights (duplicates allowed)
    for (int i = 0; i < extra; i++) {
        int u, v;
        do {
            u = rnd.next(1, N);
            v = rnd.next(1, N);
        } while (u == v);
        if (rnd.next(0, 1))
            swap(u, v);
        fights.emplace_back(u, v);
    }

    int M = (int)fights.size();

    // Output in the required format
    println(N);
    println(M);
    for (auto &e : fights)
        println(e.first, e.second);

    return 0;
}
