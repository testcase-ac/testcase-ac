#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

void addEdge(set<pair<int, int>>& used, int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    used.insert({a, b});
}

void addPath(set<pair<int, int>>& used, const vector<int>& vertices) {
    for (int i = 1; i < (int)vertices.size(); ++i) {
        addEdge(used, vertices[i - 1], vertices[i]);
    }
}

void addCycle(set<pair<int, int>>& used, const vector<int>& vertices) {
    addPath(used, vertices);
    if ((int)vertices.size() >= 3) {
        addEdge(used, vertices.back(), vertices.front());
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int v = rnd.next(2, mode == 4 ? 22 : 14);
    set<pair<int, int>> used;

    vector<int> label(v + 1);
    for (int i = 1; i <= v; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());

    if (mode == 0) {
        int last = 1;
        while (last < v) {
            int len = min(v - last + 1, rnd.next(1, 5));
            vector<int> comp;
            for (int i = 0; i < len; ++i) {
                comp.push_back(label[last + i]);
            }
            if ((int)comp.size() >= 2) {
                addPath(used, comp);
            }
            last += len;
        }
    } else if (mode == 1) {
        vector<int> vertices;
        for (int i = 1; i <= v; ++i) {
            vertices.push_back(label[i]);
        }
        if (v >= 3 && rnd.next(0, 1)) {
            addCycle(used, vertices);
        } else {
            addPath(used, vertices);
        }
    } else if (mode == 2) {
        int center = label[1];
        int leaves = rnd.next(1, v - 1);
        for (int i = 2; i <= leaves + 1; ++i) {
            addEdge(used, center, label[i]);
        }
        for (int i = leaves + 2; i + 1 <= v; i += 2) {
            addEdge(used, label[i], label[i + 1]);
        }
    } else if (mode == 3) {
        int split = rnd.next(2, v);
        for (int i = 1; i <= split; ++i) {
            for (int j = i + 1; j <= split; ++j) {
                if (rnd.next(0, 2) > 0) {
                    addEdge(used, label[i], label[j]);
                }
            }
        }
        for (int i = split + 1; i + 1 <= v; ++i) {
            addEdge(used, label[i], label[i + 1]);
        }
    } else {
        double density = rnd.next(0.08, 0.55);
        for (int i = 1; i <= v; ++i) {
            for (int j = i + 1; j <= v; ++j) {
                if (rnd.next() < density) {
                    addEdge(used, label[i], label[j]);
                }
            }
        }
    }

    if (used.empty()) {
        addEdge(used, label[1], label[2]);
    }

    vector<pair<int, int>> edges(used.begin(), used.end());
    shuffle(edges.begin(), edges.end());

    println(v, (int)edges.size());
    for (auto [a, b] : edges) {
        if (rnd.next(0, 1)) {
            swap(a, b);
        }
        println(a, b);
    }

    return 0;
}
