#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 10);
    bool wantConnected = rnd.next() < 0.7;
    vector<pair<int,int>> edges;

    auto addTree = [&](vector<int> verts) {
        int sz = verts.size();
        shuffle(verts.begin(), verts.end());
        for (int i = 1; i < sz; i++) {
            int u = verts[i-1], v = verts[i];
            int maxMul = rnd.next(1, 3);
            int mul = rnd.next(1, maxMul);
            for (int k = 0; k < mul; k++)
                edges.emplace_back(u, v);
        }
    };

    auto addExtra = [&](vector<int> verts) {
        vector<pair<int,int>> pairs;
        int sz = verts.size();
        for (int i = 0; i < sz; i++)
            for (int j = i+1; j < sz; j++)
                pairs.emplace_back(verts[i], verts[j]);
        shuffle(pairs.begin(), pairs.end());
        int hi = (int)pairs.size() + 1;
        int t = rnd.next(-1, 1);
        int cnt = rnd.wnext(hi, t);
        cnt = min(cnt, (int)pairs.size());
        for (int i = 0; i < cnt; i++) {
            int u = pairs[i].first, v = pairs[i].second;
            int maxMul = rnd.next(1, 2);
            int mul = rnd.next(1, maxMul);
            for (int k = 0; k < mul; k++)
                edges.emplace_back(u, v);
        }
    };

    if (wantConnected) {
        vector<int> verts(n);
        iota(verts.begin(), verts.end(), 1);
        addTree(verts);
        addExtra(verts);
    } else {
        int c1 = rnd.next(1, n-1);
        vector<int> all(n);
        iota(all.begin(), all.end(), 1);
        shuffle(all.begin(), all.end());
        vector<int> comp1(all.begin(), all.begin() + c1);
        vector<int> comp2(all.begin() + c1, all.end());
        addTree(comp1);
        addExtra(comp1);
        addTree(comp2);
        addExtra(comp2);
    }

    shuffle(edges.begin(), edges.end());
    int m = edges.size();
    println(n);
    println(m);
    for (auto &e : edges)
        println(e.first, e.second);

    return 0;
}
