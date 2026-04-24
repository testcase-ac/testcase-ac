#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int K = rnd.next(1, 5);
    println(K);
    vector<int> tvals = {-2, -1, 0, 1, 2};
    vector<int> capMC = {10, 20, 50, 100, 200};
    for (int tc = 0; tc < K; ++tc) {
        int N = rnd.next(2, 10);
        // Build all possible directed edges (no self-loops)
        vector<pair<int,int>> edges;
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j)
                if (i != j)
                    edges.emplace_back(i, j);
        shuffle(edges.begin(), edges.end());
        int maxEdges = edges.size();
        int t = rnd.any(tvals);
        int Mraw = rnd.wnext(maxEdges, t);
        int M = Mraw + 1;
        if (M < 2) M = 2;
        if (M > maxEdges) M = maxEdges;
        edges.resize(M);
        int capMax = rnd.any(capMC);
        int sumCap = 0;
        println(N, M);
        for (int i = 0; i < M; ++i) {
            int rem = M - i - 1;
            int maxRemainCap = 20000 - sumCap - rem;
            if (maxRemainCap < 1) maxRemainCap = 1;
            int localMax = min(capMax, maxRemainCap);
            int cap = rnd.next(1, localMax);
            sumCap += cap;
            println(edges[i].first, edges[i].second, cap);
        }
    }
    return 0;
}
