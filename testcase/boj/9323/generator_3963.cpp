#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Number of nodes
        int n = rnd.next(2, 8);
        // Build a random spanning tree to ensure connectivity
        vector<int> perm(n);
        for (int i = 0; i < n; i++) perm[i] = i + 1;
        shuffle(perm.begin(), perm.end());
        set<pair<int,int>> used;
        vector<pair<int,int>> edges;
        for (int i = 1; i < n; i++) {
            int u = perm[i];
            int v = perm[rnd.next(0, i - 1)];
            int a = min(u, v), b = max(u, v);
            used.insert({a, b});
            edges.emplace_back(a, b);
        }
        int maxEdges = n * (n - 1) / 2;
        int extraCap = maxEdges - (n - 1);
        int extra = extraCap > 0 ? rnd.next(0, min(n, extraCap)) : 0;
        int m = (n - 1) + extra;

        // Collect all possible non-tree edges
        vector<pair<int,int>> cand;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (!used.count({i, j}))
                    cand.emplace_back(i, j);
            }
        }
        shuffle(cand.begin(), cand.end());
        for (int i = 0; i < extra && i < (int)cand.size(); i++) {
            edges.push_back(cand[i]);
        }

        // Random start and end
        int start = rnd.next(1, n);
        int end = rnd.next(1, n);
        while (end == start) end = rnd.next(1, n);

        // Ticket/fine parameters
        int s = rnd.wnext(1000, rnd.next(-1, 1)) + 1;
        int p = rnd.wnext(1000, rnd.next(-1, 1)) + 1;
        int y = rnd.next(s + 1, 1000);

        // Output test case header
        println(n, m, start, end, s, p, y);
        // Output edges with c and d
        for (auto &e : edges) {
            int a = e.first, b = e.second;
            int c = rnd.next(0, 100);
            int d = rnd.wnext(1000, rnd.next(-1, 1)) + 1;
            println(a, b, c, d);
        }
    }
    return 0;
}
