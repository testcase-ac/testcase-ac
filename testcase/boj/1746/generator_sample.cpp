#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int vertexCount = rnd.next(3, 12);
    int exactTrails;
    int mode = rnd.next(5);
    if (mode == 0) {
        exactTrails = rnd.next(2, 8);
    } else if (mode == 1) {
        exactTrails = rnd.next(9, 40);
    } else if (mode == 2) {
        exactTrails = rnd.next(41, 250);
    } else if (mode == 3) {
        exactTrails = rnd.next(251, 5000);
    } else {
        exactTrails = rnd.next(900000, 1000000);
    }

    vector<int> labels;
    if (rnd.next(2) == 0) {
        for (int i = 1; i <= vertexCount; ++i) {
            labels.push_back(i);
        }
    } else {
        set<int> used;
        while ((int)labels.size() < vertexCount) {
            int x = rnd.next(1, 1000);
            if (used.insert(x).second) {
                labels.push_back(x);
            }
        }
    }
    shuffle(labels.begin(), labels.end());

    vector<pair<int, int>> edges;
    set<pair<int, int>> seen;
    for (int i = 0; i < vertexCount; ++i) {
        int u = labels[i];
        int v = labels[(i + 1) % vertexCount];
        auto edge = minmax(u, v);
        edges.push_back(edge);
        seen.insert(edge);
    }

    vector<pair<int, int>> candidates;
    for (int i = 0; i < vertexCount; ++i) {
        for (int j = i + 1; j < vertexCount; ++j) {
            auto edge = minmax(labels[i], labels[j]);
            if (!seen.count(edge)) {
                candidates.push_back(edge);
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int maxExtra = min<int>(candidates.size(), 100 - (int)edges.size());
    int extraEdges = 0;
    if (maxExtra > 0) {
        int densityMode = rnd.next(4);
        if (densityMode == 0) {
            extraEdges = rnd.next(0, min(maxExtra, 2));
        } else if (densityMode == 1) {
            extraEdges = rnd.next(0, maxExtra);
        } else if (densityMode == 2) {
            extraEdges = rnd.next(maxExtra / 2, maxExtra);
        } else {
            extraEdges = maxExtra;
        }
    }
    for (int i = 0; i < extraEdges; ++i) {
        edges.push_back(candidates[i]);
    }
    shuffle(edges.begin(), edges.end());

    int start = rnd.any(labels);
    int finish;
    if (rnd.next(5) == 0) {
        finish = start;
    } else {
        finish = rnd.any(labels);
    }

    println(exactTrails, (int)edges.size(), start, finish);
    for (auto [u, v] : edges) {
        int weight;
        int weightMode = rnd.next(4);
        if (weightMode == 0) {
            weight = rnd.next(1, 9);
        } else if (weightMode == 1) {
            weight = rnd.next(10, 100);
        } else if (weightMode == 2) {
            weight = rnd.next(900, 1000);
        } else {
            weight = rnd.next(1, 1000);
        }
        if (rnd.next(2)) {
            swap(u, v);
        }
        println(weight, u, v);
    }

    return 0;
}
