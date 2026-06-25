#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

namespace {

using Graph = vector<vector<int>>;

void addEdge(Graph& parents, int child, int parent) {
    if (child == parent) {
        return;
    }
    if (find(parents[child].begin(), parents[child].end(), parent) == parents[child].end()) {
        parents[child].push_back(parent);
    }
}

Graph makeChain(int n) {
    Graph parents(n);
    for (int i = 0; i + 1 < n; ++i) {
        addEdge(parents, i, i + 1);
    }
    return parents;
}

Graph makeForest(int n) {
    Graph parents(n);
    for (int i = 0; i < n; ++i) {
        if (i + 1 < n && rnd.next(0, 2) == 0) {
            addEdge(parents, i, rnd.next(i + 1, n - 1));
        }
    }
    return parents;
}

Graph makeClassicDiamond(int n) {
    Graph parents(n);
    addEdge(parents, 0, 1);
    addEdge(parents, 0, 2);
    addEdge(parents, 1, 3);
    addEdge(parents, 2, 3);

    for (int i = 4; i < n; ++i) {
        int maxParents = min(3, n - i - 1);
        int m = maxParents == 0 ? 0 : rnd.next(0, maxParents);
        set<int> chosen;
        while ((int)chosen.size() < m) {
            chosen.insert(rnd.next(i + 1, n - 1));
        }
        for (int parent : chosen) {
            addEdge(parents, i, parent);
        }
    }
    return parents;
}

Graph makeLayeredDiamond(int n) {
    Graph parents(n);
    int width = min(n - 2, rnd.next(2, min(5, n - 2)));
    int sink = n - 1;

    for (int i = 1; i <= width; ++i) {
        addEdge(parents, 0, i);
        addEdge(parents, i, sink);
    }

    for (int i = width + 1; i + 1 < n; ++i) {
        if (rnd.next(0, 1) == 1) {
            addEdge(parents, i, rnd.next(i + 1, n - 1));
        }
    }
    return parents;
}

Graph makeRandomDag(int n) {
    Graph parents(n);
    int maxParents = rnd.next(1, min(5, n - 1));
    for (int i = 0; i + 1 < n; ++i) {
        int available = n - i - 1;
        int m = rnd.next(0, min(maxParents, available));
        set<int> chosen;
        while ((int)chosen.size() < m) {
            chosen.insert(rnd.next(i + 1, n - 1));
        }
        for (int parent : chosen) {
            addEdge(parents, i, parent);
        }
    }
    return parents;
}

void printCase(const Graph& parents) {
    println((int)parents.size());
    for (vector<int> row : parents) {
        shuffle(row.begin(), row.end());
        printf("%d", (int)row.size());
        for (int parent : row) {
            printf(" %d", parent + 1);
        }
        printf("\n");
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        int n = rnd.next(mode >= 2 ? 4 : 1, 18);

        Graph parents;
        if (mode == 0) {
            parents = makeChain(n);
        } else if (mode == 1) {
            parents = makeForest(n);
        } else if (mode == 2) {
            parents = makeClassicDiamond(n);
        } else if (mode == 3) {
            parents = makeLayeredDiamond(n);
        } else {
            parents = makeRandomDag(n);
        }

        printCase(parents);
    }

    return 0;
}
