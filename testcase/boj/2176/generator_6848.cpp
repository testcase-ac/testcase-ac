#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: bias small or large within [2..9]
    vector<int> tN_choices = {-2, -1, 0, 1, 2};
    int tN = rnd.any(tN_choices);
    int N = rnd.wnext(8, tN) + 2;  // N in [2..9]

    // Compute max possible edges
    int maxEdges = N * (N - 1) / 2;
    // Hyper-parameter for extra edges beyond a spanning tree
    vector<int> tM_choices = {-2, -1, 0, 1, 2};
    int tM = rnd.any(tM_choices);
    int remain = maxEdges - (N - 1); // edges beyond tree
    int extra = rnd.wnext(remain + 1, tM);
    int M = (N - 1) + extra;

    // Build a random spanning tree first
    const int BASE = 10000;
    auto make_key = [&](int u, int v) {
        if (u > v) swap(u, v);
        return u * BASE + v;
    };
    set<int> used;
    vector<pair<int,int>> edges;
    for (int v = 2; v <= N; v++) {
        int u = rnd.next(1, v - 1);
        edges.emplace_back(u, v);
        used.insert(make_key(u, v));
    }

    // Collect remaining candidate edges
    vector<pair<int,int>> cand;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            if (!used.count(make_key(i, j))) {
                cand.emplace_back(i, j);
            }
        }
    }
    shuffle(cand.begin(), cand.end());
    for (int i = 0; i < extra && i < (int)cand.size(); i++) {
        edges.push_back(cand[i]);
    }

    // Assign random weights with bias
    vector<int> tW_choices = {-2, -1, 0, 1, 2};
    vector<tuple<int,int,int>> out;
    for (auto &e : edges) {
        int tW = rnd.any(tW_choices);
        int w = rnd.wnext(10000, tW) + 1;  // weight in [1..10000]
        out.emplace_back(e.first, e.second, w);
    }

    // Shuffle output edges for randomness
    shuffle(out.begin(), out.end());

    // Print result
    println(N, M);
    for (auto &t : out) {
        int u, v, w;
        tie(u, v, w) = t;
        println(u, v, w);
    }
    return 0;
}
