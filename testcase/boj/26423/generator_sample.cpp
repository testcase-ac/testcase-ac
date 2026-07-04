#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

static void addEdge(set<pair<int, int>>& edges, int a, int b) {
    if (a != b) edges.insert({a, b});
}

static void addRandomEdges(set<pair<int, int>>& edges, int n, int target) {
    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = 1; b <= n; ++b) {
            if (a != b && !edges.count({a, b})) candidates.push_back({a, b});
        }
    }
    shuffle(candidates.begin(), candidates.end());
    for (auto edge : candidates) {
        if ((int)edges.size() >= target) break;
        edges.insert(edge);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 5);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n = rnd.next(2, 12);
        int mode = rnd.next(0, 5);
        int k;
        if (mode == 0) {
            k = 1;
        } else if (mode == 1) {
            k = rnd.next(1, min(3, n));
        } else if (mode == 2) {
            k = rnd.next(max(1, n - 2), min(20, n + 2));
        } else {
            k = rnd.next(1, 20);
        }

        vector<int> p(n);
        for (int i = 0; i < n; ++i) p[i] = i + 1;
        shuffle(p.begin(), p.end());

        set<pair<int, int>> edges;
        if (mode == 0) {
            int len = rnd.next(2, n);
            for (int i = 0; i + 1 < len; ++i) addEdge(edges, p[i], p[i + 1]);
        } else if (mode == 1) {
            int len = rnd.next(2, n);
            for (int i = 0; i < len; ++i) addEdge(edges, p[i], p[(i + 1) % len]);
        } else if (mode == 2) {
            int center = p[0];
            int leaves = rnd.next(1, n - 1);
            bool outward = rnd.next(0, 1);
            for (int i = 1; i <= leaves; ++i) {
                if (outward) addEdge(edges, center, p[i]);
                else addEdge(edges, p[i], center);
            }
        } else if (mode == 3) {
            int split = rnd.next(1, n - 1);
            for (int i = 0; i < split; ++i) {
                for (int j = split; j < n; ++j) {
                    if (rnd.next(0, 99) < 45) addEdge(edges, p[i], p[j]);
                }
            }
        } else if (mode == 4) {
            for (int i = 0; i < n; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    if (rnd.next(0, 99) < 35) addEdge(edges, p[i], p[j]);
                }
            }
        } else {
            int target = rnd.next(1, min(n * (n - 1), 30));
            addRandomEdges(edges, n, target);
        }

        int target = rnd.next(max(1, (int)edges.size()), min(n * (n - 1), 30));
        addRandomEdges(edges, n, target);

        vector<pair<int, int>> out(edges.begin(), edges.end());
        shuffle(out.begin(), out.end());

        println(n, (int)out.size(), k);
        for (auto edge : out) println(edge.first, edge.second);
    }

    return 0;
}
