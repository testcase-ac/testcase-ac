#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int V = rnd.next(5, 12);
    int maxEdges = V * (V - 1) / 2;
    int E = rnd.next(max(1, V - 1), maxEdges);
    vector<pair<int,int>> all;
    for (int i = 1; i <= V; ++i)
        for (int j = i + 1; j <= V; ++j)
            all.emplace_back(i, j);
    shuffle(all.begin(), all.end());
    vector<pair<int,int>> edges(all.begin(), all.begin() + E);
    shuffle(edges.begin(), edges.end());
    println(V, E);
    for (auto &e : edges) println(e.first, e.second);
    int Q = rnd.next(3, 12);
    println(Q);
    for (int i = 0; i < Q; ++i) {
        if (E == 0) {
            println(1, 1);
            continue;
        }
        int t = rnd.next(0, 9);
        int l, r;
        if (t == 0) {
            l = 1; r = E;
        } else if (t <= 3) {
            l = r = rnd.next(1, E);
        } else if (t <= 6) {
            int len = rnd.next(1, min(3, E));
            l = rnd.next(1, E - len + 1);
            r = l + len - 1;
        } else {
            int maxlen = max(1, E / 2);
            int len = rnd.next(1, maxlen);
            l = rnd.next(1, E - len + 1);
            r = l + len - 1;
        }
        println(l, r);
    }
    return 0;
}
