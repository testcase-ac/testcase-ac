#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small graph sizes for manual verification
    int n = rnd.next(1, 15);
    vector<string> patts = {"empty","clique","path","star","cycle","bipartite","almost_clique","random"};
    string patt = rnd.any(patts);
    vector<pair<int,int>> edges;

    if (patt == "empty") {
        // no edges
    } else if (patt == "clique") {
        for (int i = 1; i <= n; i++)
            for (int j = i+1; j <= n; j++)
                edges.emplace_back(i, j);
    } else if (patt == "path") {
        for (int i = 1; i < n; i++)
            edges.emplace_back(i, i+1);
    } else if (patt == "star") {
        if (n >= 2) {
            int center = rnd.next(1, n);
            for (int i = 1; i <= n; i++)
                if (i != center)
                    edges.emplace_back(center, i);
        }
    } else if (patt == "cycle") {
        if (n >= 3) {
            for (int i = 1; i < n; i++)
                edges.emplace_back(i, i+1);
            edges.emplace_back(n, 1);
        }
    } else if (patt == "bipartite") {
        if (n >= 2) {
            int a = rnd.next(1, n-1);
            int b = n - a;
            for (int i = 1; i <= a; i++)
                for (int j = a+1; j <= n; j++)
                    edges.emplace_back(i, j);
        }
    } else if (patt == "almost_clique") {
        if (n >= 2) {
            for (int i = 1; i <= n; i++)
                for (int j = i+1; j <= n; j++)
                    edges.emplace_back(i, j);
            // remove one random edge
            int idx = rnd.next(0, (int)edges.size()-1);
            edges.erase(edges.begin() + idx);
        }
    } else if (patt == "random") {
        double d = rnd.next(0.0, 1.0);
        for (int i = 1; i <= n; i++)
            for (int j = i+1; j <= n; j++)
                if (rnd.next() < d)
                    edges.emplace_back(i, j);
    }

    // Apply a random permutation of vertex labels
    vector<int> perm(n+1);
    for (int i = 1; i <= n; i++) perm[i] = i;
    shuffle(perm.begin()+1, perm.end());
    for (auto &e : edges) {
        e.first = perm[e.first];
        e.second = perm[e.second];
        if (e.first > e.second) swap(e.first, e.second);
    }
    // Shuffle edge order
    shuffle(edges.begin(), edges.end());

    // Output
    println(n, (int)edges.size());
    for (auto &e : edges)
        println(e.first, e.second);
    return 0;
}
