#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 3);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // number of locations
        int n = rnd.wnext(12, -1) + 1;  // skew to smaller n, range [1..12]
        // starting info
        int start = rnd.next(1, n);
        int g = rnd.next(1, 20);
        int s = rnd.next(1, 20);
        // hospitals
        int m = rnd.next(1, n);
        vector<int> nodes(n);
        for (int i = 0; i < n; i++) nodes[i] = i + 1;
        shuffle(nodes.begin(), nodes.end());
        vector<int> hospitals(nodes.begin(), nodes.begin() + m);
        // roads
        int possible = n * (n - 1);
        int r = 0;
        if (n > 1) {
            int d = rnd.next(0, 2);
            int r_min, r_max;
            if (d == 0) { r_min = 0; r_max = n; }
            else if (d == 1) { r_min = n; r_max = 2 * n; }
            else { r_min = 0; r_max = 2 * n; }
            r_max = min(r_max, possible);
            r_min = min(r_min, r_max);
            r = rnd.next(r_min, r_max);
        }
        vector<pair<int,int>> edges;
        edges.reserve(possible);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (i != j)
                    edges.emplace_back(i, j);
        shuffle(edges.begin(), edges.end());
        edges.resize(r);
        // output
        println(n);
        println(start, g, s);
        println(m);
        for (int x : hospitals) println(x);
        println(r);
        for (auto &e : edges) {
            int a = e.first, b = e.second;
            int p = rnd.next(1, max(1, min(g, 20)));
            int t = rnd.next(1, max(1, s * 2));
            println(a, b, p, t);
        }
    }
    return 0;
}
