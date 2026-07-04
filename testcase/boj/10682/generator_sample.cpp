#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> allPairs(int n) {
    vector<pair<int, int>> pairs;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            pairs.push_back({a, b});
        }
    }
    return pairs;
}

void addEdge(set<pair<int, int>>& edges, int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    if (a != b) {
        edges.insert({a, b});
    }
}

vector<pair<int, int>> buildEdges(int n, int mode) {
    set<pair<int, int>> edges;

    if (mode == 0 || n == 1) {
        return {};
    }

    if (mode == 1) {
        int len = rnd.next(2, n);
        int start = rnd.next(1, n - len + 1);
        for (int v = start; v < start + len - 1; ++v) {
            addEdge(edges, v, v + 1);
        }
    } else if (mode == 2) {
        int center = rnd.next(1, n);
        int leaves = rnd.next(1, n - 1);
        vector<int> vertices;
        for (int v = 1; v <= n; ++v) {
            if (v != center) {
                vertices.push_back(v);
            }
        }
        shuffle(vertices.begin(), vertices.end());
        for (int i = 0; i < leaves; ++i) {
            addEdge(edges, center, vertices[i]);
        }
    } else if (mode == 3) {
        int firstSize = rnd.next(2, min(n, 6));
        int secondSize = rnd.next(0, min(n - firstSize, 5));
        vector<int> vertices;
        for (int v = 1; v <= n; ++v) {
            vertices.push_back(v);
        }
        shuffle(vertices.begin(), vertices.end());

        for (int i = 0; i < firstSize; ++i) {
            for (int j = i + 1; j < firstSize; ++j) {
                addEdge(edges, vertices[i], vertices[j]);
            }
        }
        for (int i = firstSize; i < firstSize + secondSize; ++i) {
            for (int j = i + 1; j < firstSize + secondSize; ++j) {
                addEdge(edges, vertices[i], vertices[j]);
            }
        }
    } else {
        vector<pair<int, int>> pairs = allPairs(n);
        shuffle(pairs.begin(), pairs.end());
        int maxM = min<int>(pairs.size(), rnd.next(1, min<int>(pairs.size(), 24)));
        for (int i = 0; i < maxM; ++i) {
            edges.insert(pairs[i]);
        }
    }

    vector<pair<int, int>> result(edges.begin(), edges.end());
    shuffle(result.begin(), result.end());
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasets = rnd.next(3, 8);
    for (int tc = 0; tc < datasets; ++tc) {
        int n;
        if (tc == 0) {
            n = 1;
        } else if (tc == 1) {
            n = rnd.next(2, 5);
        } else {
            n = rnd.next(2, 14);
        }

        int mode = rnd.next(0, 4);
        vector<pair<int, int>> edges = buildEdges(n, mode);

        println(n, static_cast<int>(edges.size()));
        for (const auto& edge : edges) {
            println(edge.first, edge.second);
        }
    }
    println(0, 0);

    return 0;
}
