#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of students
    int N = rnd.next(2, 10);
    // Generate a random topological order to ensure DAG
    vector<int> ord(N);
    iota(ord.begin(), ord.end(), 1);
    shuffle(ord.begin(), ord.end());
    // All possible forward edges in this order
    vector<pair<int,int>> cand;
    for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j)
            cand.emplace_back(ord[i], ord[j]);
    int maxM = min((int)cand.size(), 20);
    // Three hyper‐cases for diversity
    int type = rnd.next(0, 2);
    vector<pair<int,int>> edges;
    if (type == 0) {
        // Chain plus some random extras
        for (int i = 0; i + 1 < N; ++i)
            edges.emplace_back(ord[i], ord[i+1]);
        vector<pair<int,int>> rest;
        for (auto &e : cand) {
            bool isChain = false;
            for (int i = 0; i + 1 < N; ++i)
                if (e.first == ord[i] && e.second == ord[i+1]) {
                    isChain = true;
                    break;
                }
            if (!isChain) rest.push_back(e);
        }
        shuffle(rest.begin(), rest.end());
        int extraCap = max(0, maxM - (int)edges.size());
        int extra = rest.empty() ? 0 : rnd.next(0, min((int)rest.size(), extraCap));
        for (int i = 0; i < extra; ++i)
            edges.push_back(rest[i]);
    } else if (type == 1) {
        // Pure random subset
        shuffle(cand.begin(), cand.end());
        int M = cand.empty() ? 0 : rnd.next(0, maxM);
        edges.assign(cand.begin(), cand.begin() + M);
    } else {
        // Bipartite split
        int g = rnd.next(1, N - 1);
        vector<int> A(ord.begin(), ord.begin() + g);
        vector<int> B(ord.begin() + g, ord.end());
        vector<pair<int,int>> bip;
        for (int u : A)
            for (int v : B)
                bip.emplace_back(u, v);
        shuffle(bip.begin(), bip.end());
        int cap = min((int)bip.size(), 20);
        int M = bip.empty() ? 0 : rnd.next(0, cap);
        edges.assign(bip.begin(), bip.begin() + M);
    }
    int M = edges.size();
    // Output
    println(N, M);
    for (auto &e : edges)
        println(e.first, e.second);
    return 0;
}
