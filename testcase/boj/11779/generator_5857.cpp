#include "testlib.h"
#include <vector>
#include <set>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of cities
    int n = rnd.next(2, 10);
    // Start and end cities (distinct)
    int st = rnd.next(1, n);
    int en = rnd.next(1, n);
    while (en == st) en = rnd.next(1, n);

    // Density hyper-parameter for extra edges
    double dens = rnd.next(); // in [0,1)

    // Build a guaranteed path from st to en
    vector<int> path;
    path.push_back(st);
    vector<int> others;
    for (int i = 1; i <= n; i++)
        if (i != st && i != en)
            others.push_back(i);
    shuffle(others.begin(), others.end());
    int k = rnd.next(0, (int)others.size()); // number of intermediates
    for (int i = 0; i < k; i++)
        path.push_back(others[i]);
    path.push_back(en);

    vector<tuple<int,int,int>> edges;
    set<pair<int,int>> used;
    // Add edges along the path
    for (int i = 0; i + 1 < (int)path.size(); i++) {
        int u = path[i], v = path[i+1];
        int c = rnd.next(0, 100);
        edges.emplace_back(u, v, c);
        used.insert({u, v});
    }

    // Add extra random directed edges according to density
    int pathLen = (int)path.size() - 1;
    int maxPossible = n * (n - 1) - pathLen;
    int extraMax = (int)round(dens * maxPossible);
    if (extraMax < 0) extraMax = 0;
    int extra = rnd.next(0, extraMax);
    int added = 0;
    while (added < extra) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (u == v || used.count({u, v})) continue;
        int c = rnd.next(0, 100);
        edges.emplace_back(u, v, c);
        used.insert({u, v});
        added++;
    }

    // Shuffle edge list to vary order
    shuffle(edges.begin(), edges.end());
    int m = edges.size();

    // Output
    println(n);
    println(m);
    for (auto &t : edges) {
        int u, v, c;
        tie(u, v, c) = t;
        println(u, v, c);
    }
    println(st, en);

    return 0;
}
