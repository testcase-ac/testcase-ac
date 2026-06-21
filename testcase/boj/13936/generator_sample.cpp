#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>
using namespace std;

static void addEdge(vector<set<int>>& graph, int from, int to) {
    if (from == to || graph[from].size() >= 10) {
        return;
    }
    graph[from].insert(to);
}

static vector<int> shuffledNodes(int n) {
    vector<int> nodes;
    for (int i = 1; i <= n; ++i) {
        nodes.push_back(i);
    }
    shuffle(nodes.begin(), nodes.end());
    return nodes;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 18);
    if (mode == 0) {
        n = rnd.next(3, 14);
    } else if (mode == 1) {
        n = rnd.next(4, 16);
    } else if (mode == 4) {
        n = rnd.next(5, 18);
    }

    vector<set<int>> graph(n + 1);

    if (mode == 0) {
        int len = rnd.next(2, n);
        for (int i = 1; i < len; ++i) {
            addEdge(graph, i, i + 1);
        }
        for (int i = 1; i <= n; ++i) {
            int extra = rnd.next(0, 2);
            for (int e = 0; e < extra; ++e) {
                addEdge(graph, i, rnd.next(1, n));
            }
        }
    } else if (mode == 1) {
        int branchA = 2;
        int branchB = 3;
        addEdge(graph, 1, branchA);
        addEdge(graph, 1, branchB);
        for (int i = 4; i <= n; ++i) {
            addEdge(graph, rnd.next(1, i - 1), i);
        }
        if (rnd.next(0, 1)) {
            addEdge(graph, branchA, branchB);
        }
        if (rnd.next(0, 1)) {
            addEdge(graph, branchB, branchA);
        }
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            addEdge(graph, i, rnd.next(1, i - 1));
        }
        for (int i = 1; i <= n; ++i) {
            if (rnd.next(0, 3) == 0) {
                addEdge(graph, i, rnd.next(1, n));
            }
        }
    } else if (mode == 3) {
        int attempts = rnd.next(n, min(4 * n, n * 10));
        for (int i = 0; i < attempts; ++i) {
            addEdge(graph, rnd.next(1, n), rnd.next(1, n));
        }
    } else if (mode == 4) {
        int meet = rnd.next(2, n);
        addEdge(graph, 1, meet);
        for (int i = 2; i <= n; ++i) {
            if (i != meet && rnd.next(0, 1)) {
                addEdge(graph, meet, i);
            }
        }
        for (int i = 2; i <= n; ++i) {
            if (i != meet && rnd.next(0, 2) == 0) {
                addEdge(graph, i, meet);
            }
        }
    } else {
        int split = rnd.next(2, n);
        for (int i = 1; i + 1 < split; ++i) {
            addEdge(graph, i, i + 1);
        }
        for (int i = split; i < n; ++i) {
            addEdge(graph, i, i + 1);
        }
        for (int i = split; i <= n; ++i) {
            if (rnd.next(0, 2) == 0) {
                addEdge(graph, i, rnd.next(split, n));
            }
        }
    }

    vector<int> nodes = shuffledNodes(n);
    int maxIron = min(n - 1, max(1, n / 3));
    int m = rnd.next(1, maxIron);
    int maxCoal = min(n - m, max(1, n / 3));
    int k = rnd.next(1, maxCoal);

    vector<int> iron(nodes.begin(), nodes.begin() + m);
    vector<int> coal(nodes.begin() + m, nodes.begin() + m + k);
    sort(iron.begin(), iron.end());
    sort(coal.begin(), coal.end());

    println(n, m, k);
    println(iron);
    println(coal);
    for (int i = 1; i <= n; ++i) {
        vector<int> neighbours(graph[i].begin(), graph[i].end());
        printf("%d", static_cast<int>(neighbours.size()));
        for (int to : neighbours) {
            printf(" %d", to);
        }
        printf("\n");
    }

    return 0;
}
