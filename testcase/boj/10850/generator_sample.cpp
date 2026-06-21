#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 12);
    vector<set<int>> graph(n);

    auto addEdgeByOrder = [&](const vector<int>& order, int fromPos, int toPos) {
        if (fromPos < toPos) {
            graph[order[fromPos]].insert(order[toPos]);
        }
    };

    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end());

    if (mode == 0) {
        // Mixed chains and isolated planets.
        int i = 0;
        while (i + 1 < n) {
            int len = min(n - i, rnd.next(1, 4));
            for (int j = 0; j + 1 < len; ++j) {
                addEdgeByOrder(order, i + j, i + j + 1);
            }
            i += len;
        }
    } else if (mode == 1) {
        // Branching/merging DAG with sparse forward jumps.
        for (int i = 0; i < n; ++i) {
            int maxTargets = min(3, n - i - 1);
            int targets = maxTargets == 0 ? 0 : rnd.next(0, maxTargets);
            vector<int> candidates;
            for (int j = i + 1; j < n; ++j) {
                candidates.push_back(j);
            }
            shuffle(candidates.begin(), candidates.end());
            for (int j = 0; j < targets; ++j) {
                addEdgeByOrder(order, i, candidates[j]);
            }
        }
    } else if (mode == 2) {
        // Layered graph: many sources can point to common later planets.
        int firstCut = rnd.next(1, n);
        int secondCut = rnd.next(firstCut, n);
        for (int i = 0; i < firstCut; ++i) {
            for (int j = firstCut; j < secondCut; ++j) {
                if (rnd.next(0, 99) < 55) {
                    addEdgeByOrder(order, i, j);
                }
            }
        }
        for (int i = firstCut; i < secondCut; ++i) {
            for (int j = secondCut; j < n; ++j) {
                if (rnd.next(0, 99) < 45) {
                    addEdgeByOrder(order, i, j);
                }
            }
        }
    } else if (mode == 3) {
        // Dense but still small DAG.
        int probability = rnd.next(25, 80);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next(0, 99) < probability) {
                    addEdgeByOrder(order, i, j);
                }
            }
        }
    } else {
        // Nearly empty graph with one optional short path.
        if (n >= 2 && rnd.next(0, 1)) {
            int start = rnd.next(0, n - 2);
            int len = rnd.next(1, min(3, n - start - 1));
            for (int j = 0; j < len; ++j) {
                addEdgeByOrder(order, start + j, start + j + 1);
            }
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        vector<int> destinations(graph[i].begin(), graph[i].end());
        printf("%d", static_cast<int>(destinations.size()));
        for (int destination : destinations) {
            printf(" %d", destination);
        }
        printf("\n");
    }

    return 0;
}
