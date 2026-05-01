#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        int N = rnd.next(3, 10);
        int Q = rnd.next(1, 10);
        // Generate tree with diverse shapes
        vector<pair<int,int>> edges;
        int treeType = rnd.next(0, 3);
        if (treeType == 0) {
            // Chain
            for (int i = 1; i < N; i++)
                edges.emplace_back(i, i+1);
        } else if (treeType == 1) {
            // Star
            int center = rnd.next(1, N);
            for (int i = 1; i <= N; i++)
                if (i != center)
                    edges.emplace_back(center, i);
        } else if (treeType == 2) {
            // Balanced binary-like
            for (int i = 2; i <= N; i++)
                edges.emplace_back(i/2, i);
        } else {
            // Random tree
            for (int i = 2; i <= N; i++)
                edges.emplace_back(rnd.next(1, i-1), i);
        }
        shuffle(edges.begin(), edges.end());
        int R = rnd.next(1, N);
        // Output test case header
        println(N, Q, R);
        // Output edges
        for (auto &e : edges)
            println(e.first, e.second);
        // Generate queries
        double p0 = rnd.next(0.0, 1.0);
        vector<pair<int,int>> queries;
        bool haveType1 = false;
        for (int i = 0; i < Q; i++) {
            int S = (rnd.next() < p0 ? 0 : 1);
            int U = rnd.next(1, N);
            if (S == 1) haveType1 = true;
            queries.emplace_back(S, U);
        }
        if (!haveType1) {
            // Ensure at least one query to answer
            queries[Q-1].first = 1;
            queries[Q-1].second = rnd.next(1, N);
        }
        for (auto &q : queries)
            println(q.first, q.second);
    }
    return 0;
}
