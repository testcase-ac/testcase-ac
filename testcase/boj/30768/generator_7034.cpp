#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of cities
    int n = rnd.next(5, 10);
    // number of companies
    int k = rnd.next(2, 8);
    // build a random spanning tree to ensure connectivity
    vector<pair<int,int>> edges;
    for (int i = 2; i <= n; i++) {
        int j = rnd.next(1, i-1);
        edges.emplace_back(i, j);
    }
    // collect all possible other edges
    vector<pair<int,int>> other;
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            bool inTree = false;
            for (auto &e : edges) {
                if ((e.first==i && e.second==j) || (e.first==j && e.second==i)) {
                    inTree = true;
                    break;
                }
            }
            if (!inTree) other.emplace_back(i, j);
        }
    }
    // add some extra edges
    shuffle(other.begin(), other.end());
    int extra = rnd.next(0, min((int)other.size(), n));
    for (int i = 0; i < extra; i++)
        edges.push_back(other[i]);
    int m = edges.size();
    // choose which companies actually appear on edges (others will be absent)
    int maxUses = min(k, min(m, 3));
    int compUsedCount = rnd.next(1, maxUses);
    vector<int> pool;
    for (int i = 1; i <= k; i++) pool.push_back(i);
    shuffle(pool.begin(), pool.end());
    vector<int> compList(pool.begin(), pool.begin() + compUsedCount);
    // free edge probability
    double freeProb = rnd.next();
    // assign companies to edges
    vector<tuple<int,int,int>> ed;
    for (auto &e : edges) {
        int u = e.first, v = e.second;
        int c;
        if (rnd.next() < freeProb) {
            c = 0;
        } else {
            c = rnd.any(compList);
        }
        ed.emplace_back(u, v, c);
    }
    // shuffle final edge order
    shuffle(ed.begin(), ed.end());
    // choose capitals
    int a = rnd.next(1, n), b = rnd.next(1, n);
    while (b == a) b = rnd.next(1, n);
    // output
    println(n, m, k);
    for (auto &t : ed) {
        int u, v, c;
        tie(u, v, c) = t;
        println(u, v, c);
    }
    println(a, b);
    return 0;
}
