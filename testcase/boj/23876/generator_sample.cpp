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

void addPath(set<Edge>& edges, int l, int r) {
    for (int i = l; i < r; ++i) addEdge(edges, i, i + 1);
}

vector<Edge> makeCase(int mode, int n) {
    set<Edge> edges;

    if (mode == 0) {
        addPath(edges, 1, n);
    } else if (mode == 1) {
        int leftEnd = rnd.next(1, max(1, n / 3));
        int rightStart = rnd.next(max(leftEnd + 1, 2 * n / 3), n);
        addPath(edges, 1, leftEnd);
        addPath(edges, rightStart, n);
    } else if (mode == 2) {
        int midL = rnd.next(2, max(2, n / 2));
        int midR = rnd.next(midL, n - 1);
        addPath(edges, 1, rnd.next(1, midL - 1));
        addPath(edges, midL, midR);
        addPath(edges, rnd.next(midR + 1, n), n);
    } else if (mode == 3) {
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                int dist = j - i;
                if (dist == 1 ? rnd.next(0, 2) == 0 : rnd.next(0, 7) == 0) {
                    addEdge(edges, i, j);
                }
            }
        }
    } else {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i + 1;
        shuffle(order.begin(), order.end());

        int comps = rnd.next(2, min(n, 5));
        vector<vector<int>> groups(comps);
        for (int i = 0; i < n; ++i) groups[i % comps].push_back(order[i]);

        for (auto& group : groups) {
            sort(group.begin(), group.end());
            for (int i = 1; i < static_cast<int>(group.size()); ++i) {
                addEdge(edges, group[i - 1], group[i]);
            }
            for (int i = 0; i < static_cast<int>(group.size()); ++i) {
                for (int j = i + 2; j < static_cast<int>(group.size()); ++j) {
                    if (rnd.next(0, 3) == 0) addEdge(edges, group[i], group[j]);
                }
            }
        }
    }

    vector<Edge> result(edges.begin(), edges.end());
    shuffle(result.begin(), result.end());
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(5, 12);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = tc < 5 ? tc : rnd.next(0, 4);
        int n = mode == 0 ? rnd.next(2, 16) : rnd.next(3, 18);
        vector<Edge> edges = makeCase(mode, n);

        println(n, static_cast<int>(edges.size()));
        for (auto [a, b] : edges) println(a, b);
    }

    return 0;
}
