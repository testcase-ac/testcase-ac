#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

void addEdge(set<Edge>& edges, int a, int b) {
    if (a == b) return;
    edges.insert(minmax(a, b));
}

void addRandomEdges(set<Edge>& edges, int p, int target) {
    vector<Edge> candidates;
    for (int i = 0; i < p; ++i) {
        for (int j = i + 1; j < p; ++j) {
            candidates.emplace_back(i, j);
        }
    }
    shuffle(candidates.begin(), candidates.end());

    for (auto [a, b] : candidates) {
        if ((int)edges.size() >= target) break;
        addEdge(edges, a, b);
    }
}

vector<int> shuffledMiddlePlanets(int p) {
    vector<int> middle;
    for (int i = 2; i < p; ++i) {
        middle.push_back(i);
    }
    shuffle(middle.begin(), middle.end());
    return middle;
}

vector<Edge> makeCase(int mode, int p) {
    set<Edge> edges;
    vector<int> middle = shuffledMiddlePlanets(p);

    if (mode == 0) {
        addEdge(edges, 0, 1);
        int spokes = rnd.next(0, min(p - 2, 5));
        for (int i = 0; i < spokes; ++i) {
            addEdge(edges, rnd.next(0, 1), middle[i]);
        }
    } else if (mode == 1) {
        int via = middle[0];
        addEdge(edges, 0, via);
        addEdge(edges, 1, via);
        for (int i = 1; i < (int)middle.size(); ++i) {
            if (rnd.next(2)) addEdge(edges, via, middle[i]);
        }
    } else if (mode == 2) {
        int pathLen = rnd.next(3, min(p, 8));
        vector<int> path = {0};
        for (int i = 0; i < pathLen - 2; ++i) {
            path.push_back(middle[i]);
        }
        path.push_back(1);
        for (int i = 0; i + 1 < (int)path.size(); ++i) {
            addEdge(edges, path[i], path[i + 1]);
        }
    } else if (mode == 3) {
        int branches = rnd.next(2, min(p - 2, 6));
        for (int i = 0; i < branches; ++i) {
            addEdge(edges, 0, middle[i]);
            addEdge(edges, 1, middle[i]);
        }
        for (int i = 0; i < branches; ++i) {
            for (int j = i + 1; j < branches; ++j) {
                if (rnd.next(3) == 0) addEdge(edges, middle[i], middle[j]);
            }
        }
    } else {
        for (int i = 1; i < p; ++i) {
            addEdge(edges, i, rnd.next(0, i - 1));
        }
        if (!edges.count({0, 1})) {
            int via = middle[0];
            addEdge(edges, 0, via);
            addEdge(edges, 1, via);
        }
    }

    int maxEdges = min(2000, p * (p - 1) / 2);
    int compactLimit = min(maxEdges, max((int)edges.size(), p + rnd.next(0, min(12, p))));
    if (mode == 4) {
        compactLimit = rnd.next((int)edges.size(), min(maxEdges, max((int)edges.size(), p * 2)));
    } else if (rnd.next(3) == 0) {
        compactLimit = rnd.next((int)edges.size(), min(maxEdges, (int)edges.size() + 5));
    }
    addRandomEdges(edges, p, compactLimit);

    vector<Edge> result(edges.begin(), edges.end());
    shuffle(result.begin(), result.end());
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 12);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = tc < 5 ? tc : rnd.next(0, 4);
        int p = mode == 0 ? rnd.next(2, 8) : rnd.next(4, 14);
        vector<Edge> edges = makeCase(mode, p);

        println(p, (int)edges.size());
        for (int i = 0; i < (int)edges.size(); ++i) {
            if (i > 0) printf(" ");
            printf("%d,%d", edges[i].first, edges[i].second);
        }
        printf("\n");
    }

    return 0;
}
