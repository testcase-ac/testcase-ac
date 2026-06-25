#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

void addEdge(vector<pair<int, int>>& edges, int a, int b) {
    if (rnd.next(2)) swap(a, b);
    edges.emplace_back(a, b);
}

vector<pair<int, int>> allPairs(int p) {
    vector<pair<int, int>> pairs;
    for (int i = 0; i < p; ++i) {
        for (int j = i + 1; j < p; ++j) {
            pairs.emplace_back(i, j);
        }
    }
    shuffle(pairs.begin(), pairs.end());
    return pairs;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 10);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(6);
        int p = rnd.next(1, mode == 5 ? 16 : 12);
        vector<pair<int, int>> edges;

        if (mode == 0) {
            int target = rnd.next(0, min(10, p * (p - 1) / 2));
            for (auto [a, b] : allPairs(p)) {
                addEdge(edges, a, b);
                if ((int)edges.size() == target) break;
            }
        } else if (mode == 1 && p >= 2) {
            for (int i = 1; i < p; ++i) {
                addEdge(edges, i, rnd.next(0, i - 1));
            }
        } else if (mode == 2 && p >= 3) {
            for (int i = 0; i < p; ++i) {
                addEdge(edges, i, (i + 1) % p);
            }
            int extra = rnd.next(0, min(8, p * (p - 1) / 2 - p));
            set<pair<int, int>> seen;
            for (int i = 0; i < p; ++i) seen.insert({min(i, (i + 1) % p), max(i, (i + 1) % p)});
            for (auto [a, b] : allPairs(p)) {
                if (extra == 0) break;
                if (!seen.insert({a, b}).second) continue;
                addEdge(edges, a, b);
                --extra;
            }
        } else if (mode == 3 && p >= 4) {
            int left = rnd.next(2, p - 2);
            for (int i = 0; i < left; ++i) addEdge(edges, i, (i + 1) % left);
            for (int i = left; i < p; ++i) addEdge(edges, i, left + (i + 1 - left) % (p - left));
            addEdge(edges, rnd.next(0, left - 1), rnd.next(left, p - 1));
        } else if (mode == 4 && p >= 2) {
            auto pairs = allPairs(p);
            int target = rnd.next(p - 1, min((int)pairs.size(), 30));
            for (int i = 0; i < target; ++i) {
                addEdge(edges, pairs[i].first, pairs[i].second);
            }
        } else {
            p = max(p, 3);
            int baseEdges = rnd.next(1, min(6, p * (p - 1) / 2));
            auto pairs = allPairs(p);
            for (int i = 0; i < baseEdges; ++i) {
                int copies = rnd.next(1, 4);
                for (int j = 0; j < copies; ++j) {
                    addEdge(edges, pairs[i].first, pairs[i].second);
                }
            }
        }

        shuffle(edges.begin(), edges.end());
        println(p, (int)edges.size());
        for (auto [a, b] : edges) {
            println(a, b);
        }
    }

    println(0, 0);
    return 0;
}
