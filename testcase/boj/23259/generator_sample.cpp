#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

const vector<pair<int, int>> ALL_EDGES = {
    {1, 2}, {1, 3}, {1, 4}, {1, 5}, {2, 3},
    {2, 4}, {2, 5}, {3, 4}, {3, 5}, {4, 5},
};

vector<pair<int, int>> edgesFromMask(int mask) {
    vector<pair<int, int>> edges;
    for (int i = 0; i < (int)ALL_EDGES.size(); ++i) {
        if (mask & (1 << i)) edges.push_back(ALL_EDGES[i]);
    }
    return edges;
}

vector<pair<int, int>> relabel(vector<pair<int, int>> edges) {
    vector<int> p = {1, 2, 3, 4, 5};
    shuffle(p.begin(), p.end());

    for (auto& edge : edges) {
        edge.first = p[edge.first - 1];
        edge.second = p[edge.second - 1];
        if (rnd.next(2)) swap(edge.first, edge.second);
    }
    shuffle(edges.begin(), edges.end());
    return edges;
}

int randomMaskWithEdgeCount(int e) {
    vector<int> ids;
    for (int i = 0; i < 10; ++i) ids.push_back(i);
    shuffle(ids.begin(), ids.end());

    int mask = 0;
    for (int i = 0; i < e; ++i) mask |= 1 << ids[i];
    return mask;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    vector<vector<pair<int, int>>> stars;

    if (mode == 0) {
        int n = rnd.next(1, 18);
        for (int i = 0; i < n; ++i) {
            int e = rnd.next(0, 10);
            stars.push_back(relabel(edgesFromMask(randomMaskWithEdgeCount(e))));
        }
    } else if (mode == 1) {
        int groups = rnd.next(2, 6);
        for (int g = 0; g < groups; ++g) {
            int base = rnd.next(0, (1 << 10) - 1);
            int copies = rnd.next(1, 4);
            for (int i = 0; i < copies; ++i) {
                stars.push_back(relabel(edgesFromMask(base)));
            }
        }
    } else if (mode == 2) {
        vector<int> edgeCounts = {0, 1, 2, 3, 7, 8, 9, 10};
        shuffle(edgeCounts.begin(), edgeCounts.end());
        int n = rnd.next(4, (int)edgeCounts.size());
        for (int i = 0; i < n; ++i) {
            stars.push_back(relabel(edgesFromMask(randomMaskWithEdgeCount(edgeCounts[i]))));
        }
    } else if (mode == 3) {
        int pairs = rnd.next(2, 6);
        for (int i = 0; i < pairs; ++i) {
            int base = rnd.next(0, (1 << 10) - 1);
            stars.push_back(relabel(edgesFromMask(base)));
            stars.push_back(relabel(edgesFromMask(((1 << 10) - 1) ^ base)));
        }
    } else {
        int base = rnd.next(0, (1 << 10) - 1);
        int uniqueCount = rnd.next(1, 5);
        int duplicateCount = rnd.next(2, 6);
        for (int i = 0; i < duplicateCount; ++i) {
            stars.push_back(relabel(edgesFromMask(base)));
        }
        for (int i = 0; i < uniqueCount; ++i) {
            int mask = rnd.next(0, (1 << 10) - 1);
            stars.push_back(relabel(edgesFromMask(mask)));
        }
    }

    println((int)stars.size());
    for (const auto& edges : stars) {
        println((int)edges.size());
        for (auto edge : edges) println(edge.first, edge.second);
    }

    return 0;
}
