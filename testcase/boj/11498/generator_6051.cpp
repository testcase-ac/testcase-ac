#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 4);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        int N = rnd.next(1, 12);
        int cat = rnd.next(0, 2);
        vector<pair<int,int>> edges;
        if (cat == 0) {
            // DAG with random edges
            vector<int> order(N);
            for (int i = 0; i < N; i++) order[i] = i + 1;
            shuffle(order.begin(), order.end());
            vector<pair<int,int>> pot;
            for (int i = 0; i < N; i++)
                for (int j = i + 1; j < N; j++)
                    pot.emplace_back(order[i], order[j]);
            int maxE = pot.size();
            int limit = min(maxE, 20);
            int M = maxE > 0 ? rnd.next(0, limit) : 0;
            shuffle(pot.begin(), pot.end());
            for (int i = 0; i < M; i++)
                edges.push_back(pot[i]);
        } else if (cat == 1) {
            // Single even-length cycle
            if (N >= 2) {
                vector<int> nodes(N);
                for (int i = 0; i < N; i++) nodes[i] = i + 1;
                shuffle(nodes.begin(), nodes.end());
                vector<int> evenLs;
                for (int L = 2; L <= N; L += 2) evenLs.push_back(L);
                int L = rnd.any(evenLs);
                for (int i = 0; i < L; i++) {
                    int u = nodes[i];
                    int v = nodes[(i+1)%L];
                    edges.emplace_back(u, v);
                }
            }
        } else {
            // Single odd-length cycle
            if (N >= 3) {
                vector<int> nodes(N);
                for (int i = 0; i < N; i++) nodes[i] = i + 1;
                shuffle(nodes.begin(), nodes.end());
                vector<int> oddLs;
                for (int L = 3; L <= N; L += 2) oddLs.push_back(L);
                int L = rnd.any(oddLs);
                for (int i = 0; i < L; i++) {
                    int u = nodes[i];
                    int v = nodes[(i+1)%L];
                    edges.emplace_back(u, v);
                }
            }
        }
        int M = edges.size();
        println(N, M);
        for (auto &e : edges)
            println(e.first, e.second);
    }
    return 0;
}
