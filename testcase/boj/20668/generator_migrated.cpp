#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) 
{
    registerGen(argc, argv, 1);

    int N = 10000;
    int M = 100000;
    
    int pattern = rnd.next(0, 2); 
    
    vector<tuple<int, int, int, int>> edges;
    set<pair<int, int>> used;

    auto addEdge = [&](int u, int v, int l, int k) 
  {
        if (u == v) return;
        if (u > v) swap(u, v);
        if (used.count({u, v})) return;
        used.insert({u, v});
        edges.push_back({u, v, l, k});
    };

    if (pattern == 0) 
    {
        for (int i = 1; i < N; i++) {
            int L = rnd.next(90000, 100000);
            int K = 10;
            
            if (i <= 10) K = i;
            if (N - i <= 10) K = max(1, N - i);
            
            addEdge(i, i + 1, L, K);
        }
    } 
    else if (pattern == 1) 
    {
        for (int i = 1; i < N; i++) 
        {
            addEdge(i, i + 1, rnd.next(50000, 100000), rnd.next(1, 10)); // 기본 뼈대
        }
        for (int i = 4; i <= N; i++) 
        {
            if (rnd.next(0, 3) == 0) addEdge(2, i, rnd.next(1000, 100000), rnd.next(8, 10));
            if (rnd.next(0, 3) == 0) addEdge(3, i, rnd.next(1000, 100000), rnd.next(1, 5));
        }
    } 
    else 
    {
        for (int i = 1; i < N; i++) {
            addEdge(i, i + 1, rnd.next(80000, 100000), rnd.next(1, 10));
        }
    }

    while (edges.size() < M) 
    {
        int u = rnd.next(1, N);
        int v = rnd.next(1, N);
        int L = rnd.next(1, 100000);
        int K = rnd.next(1, 10);
        addEdge(u, v, L, K);
    }

    shuffle(edges.begin(), edges.end());

    println(N, edges.size());
    for (auto& e : edges) 
    {
        println(get<0>(e), get<1>(e), get<2>(e), get<3>(e));
    }

    return 0;
}
