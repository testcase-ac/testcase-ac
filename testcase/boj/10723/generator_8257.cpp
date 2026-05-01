#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 3);
    println(T);
    vector<int> weightChoices = {0, 1, 5, 10, 100, 1000, 100000, 10000000};
    for (int tc = 0; tc < T; tc++) {
        int n = rnd.next(1, 7);
        int maxM = (n <= 1 ? 1 : min(6, n * (n - 1) / 2));
        int m = rnd.next(1, maxM);
        println(n, m);
        vector<pair<int,int>> baseEdges;
        // initial tree
        for (int i = 1; i < n; i++) {
            int u = rnd.next(0, i - 1);
            int c = rnd.any(weightChoices);
            println(u, c);
            baseEdges.emplace_back(u, i);
        }
        // new roads
        for (int i = 0; i < m; i++) {
            double p = rnd.next();
            int u, v;
            if (!baseEdges.empty() && p < 0.1) {
                auto e = rnd.any(baseEdges);
                u = e.first; v = e.second;
            } else if (p < 0.2) {
                u = rnd.next(0, n - 1); v = u;
            } else if (!baseEdges.empty() && p < 0.4) {
                auto e = rnd.any(baseEdges);
                u = e.second; v = e.first;
            } else {
                if (n > 1) {
                    u = rnd.next(0, n - 1);
                    v = rnd.next(0, n - 1);
                    if (u == v) v = (u + 1) % n;
                } else {
                    u = v = 0;
                }
            }
            int c = rnd.any(weightChoices);
            println(u, v, c);
        }
    }
    return 0;
}
