#include "testlib.h"
using namespace std;

string randomItems() {
    static const char items[4] = {'B', 'J', 'M', 'P'};
    int r = rnd.next(0, 99);
    int k;
    if (r < 25) k = 1;
    else if (r < 55) k = 2;
    else if (r < 85) k = 3;
    else k = 4;

    vector<int> idx = {0, 1, 2, 3};
    shuffle(idx.begin(), idx.end());
    string s;
    for (int i = 0; i < k; ++i)
        s += items[idx[i]];
    sort(s.begin(), s.end());
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // With small probability, output one of the samples from the statement
    int sampleProb = rnd.next(0, 99);
    if (sampleProb < 7) {
        // Example 1
        println(3, 3);
        println(1, 2, "BMJ");
        println(2, 3, "MJP");
        println(3, 1, "JPB");
        println(5);
        return 0;
    } else if (sampleProb < 14) {
        // Example 2
        println(3, 4);
        println(1, 2, "B");
        println(2, 1, "P");
        println(1, 3, "J");
        println(3, 1, "M");
        println(8);
        return 0;
    } else if (sampleProb < 21) {
        // Example 3
        println(5, 7);
        println(1, 2, "B");
        println(2, 4, "M");
        println(1, 3, "J");
        println(3, 4, "MB");
        println(4, 1, "JP");
        println(4, 5, "J");
        println(5, 1, "P");
        println(7);
        return 0;
    }

    // General random generation
    int N;
    // Choose N from {2-4, 5-8, 9-12} with bias towards smaller values
    int bucket = rnd.next(0, 4);
    if (bucket == 0) N = rnd.next(2, 3);
    else if (bucket <= 2) N = rnd.next(2, 6);
    else if (bucket == 3) N = rnd.next(5, 8);
    else N = rnd.next(7, 12);

    int maxDirEdges = N * (N - 1);
    int Rmax = min(maxDirEdges, 30);

    // Density type: sparse / medium / dense
    int densType = rnd.next(0, 2);
    int Rtarget;
    if (densType == 0) {
        int lo = max(1, N - 1);
        int hi = min(N + 2, Rmax);
        if (lo > hi) lo = hi;
        Rtarget = rnd.next(lo, hi);
    } else if (densType == 1) {
        int lo = max(0, maxDirEdges / 4);
        int hi = max(1, maxDirEdges / 2);
        lo = min(lo, Rmax);
        hi = min(hi, Rmax);
        if (lo > hi) lo = hi;
        Rtarget = rnd.next(lo, hi);
    } else {
        int lo = max(1, maxDirEdges / 2);
        int hi = Rmax;
        if (lo > hi) lo = hi;
        Rtarget = rnd.next(lo, hi);
    }
    Rtarget = max(2, min(Rtarget, Rmax));

    vector<vector<bool>> hasEdge(N + 1, vector<bool>(N + 1, false));
    vector<tuple<int,int,string>> edges;

    auto addEdge = [&](int u, int v, const string& s) {
        if (u == v) return;
        if (hasEdge[u][v]) return;
        hasEdge[u][v] = true;
        edges.emplace_back(u, v, s);
    };

    // With high probability, ensure at least one simple valid path via 1 <-> 2
    bool ensurePath = (N >= 2) && (rnd.next(0, 99) < 70);
    if (ensurePath) {
        addEdge(1, 2, "BJMP"); // all ingredients
        addEdge(2, 1, "BJMP");
    }
    int baseCount = (int)edges.size();
    if (Rtarget < baseCount) Rtarget = baseCount;

    // Add remaining random edges
    while ((int)edges.size() < Rtarget) {
        int u = rnd.next(1, N);
        int v = rnd.next(1, N - 1);
        if (v >= u) ++v;
        if (hasEdge[u][v]) continue;
        string s = randomItems();
        addEdge(u, v, s);
    }

    // Shuffle edges for variability
    shuffle(edges.begin(), edges.end());

    // Choose K with mixed scales
    int K;
    int roll = rnd.next(1, 100);
    if (roll <= 40) {
        K = rnd.next(1, 15);
    } else if (roll <= 70) {
        K = rnd.next(16, 50);
    } else if (roll <= 90) {
        K = rnd.next(51, 200);
    } else {
        K = rnd.next(201, 1000000000);
    }

    println(N, (int)edges.size());
    for (auto &e : edges) {
        int u, v;
        string s;
        tie(u, v, s) = e;
        println(u, v, s);
    }
    println(K);

    return 0;
}
