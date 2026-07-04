#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    set<pair<int, int>> edgeSet;

    auto addEdge = [&](int man, int woman) {
        edgeSet.insert({man, woman});
    };

    if (mode == 0) {
        // Empty graph: every nonempty male subset is a certificate.
    } else if (mode == 1) {
        for (int man = 1; man <= n; ++man) {
            for (int woman = 1; woman <= n; ++woman) {
                addEdge(man, woman);
            }
        }
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        int men = rnd.next(2, n);
        int women = rnd.next(1, men - 1);
        for (int man = 1; man <= men; ++man) {
            int degree = rnd.next(1, women);
            vector<int> choices;
            for (int woman = 1; woman <= women; ++woman) {
                choices.push_back(woman);
            }
            shuffle(choices.begin(), choices.end());
            for (int i = 0; i < degree; ++i) {
                addEdge(man, choices[i]);
            }
        }
        for (int man = men + 1; man <= n; ++man) {
            if (rnd.next(0, 1) == 1) {
                addEdge(man, rnd.next(1, n));
            }
        }
    } else if (mode == 3) {
        for (int i = 1; i <= n; ++i) {
            addEdge(i, i);
        }
        int extras = rnd.next(0, min(n * n - n, 3 * n));
        for (int tries = 0; tries < 5 * extras; ++tries) {
            if ((int)edgeSet.size() >= n + extras) {
                break;
            }
            addEdge(rnd.next(1, n), rnd.next(1, n));
        }
    } else if (mode == 4) {
        int maxEdges = n * n;
        int target = rnd.next(0, min(maxEdges, 4 * n));
        while ((int)edgeSet.size() < target) {
            addEdge(rnd.next(1, n), rnd.next(1, n));
        }
    } else {
        int hubs = rnd.next(1, n);
        for (int woman = 1; woman <= hubs; ++woman) {
            int degree = rnd.next(1, n);
            for (int i = 0; i < degree; ++i) {
                addEdge(rnd.next(1, n), woman);
            }
        }
    }

    vector<pair<int, int>> edges(edgeSet.begin(), edgeSet.end());
    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
