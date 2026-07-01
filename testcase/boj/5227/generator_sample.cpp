#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

static void printCase(int n, const vector<pair<int, int>>& edges, const vector<int>& stones) {
    println(n, static_cast<int>(edges.size()));
    for (int i = 0; i < static_cast<int>(edges.size()); ++i) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d %d", edges[i].first, edges[i].second);
    }
    printf("\n");
    println(stones);
}

static vector<int> randomPermutation(int n) {
    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end());
    return order;
}

static vector<pair<int, int>> buildEdges(int n, int mode) {
    vector<int> order = randomPermutation(n);
    vector<pair<int, int>> edges;

    if (mode == 0) {
        return edges;
    }

    if (mode == 1) {
        for (int i = 0; i + 1 < n; ++i) {
            edges.push_back({order[i], order[i + 1]});
        }
        return edges;
    }

    vector<pair<int, int>> candidates;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            candidates.push_back({order[i], order[j]});
        }
    }
    if (candidates.empty()) {
        return edges;
    }
    shuffle(candidates.begin(), candidates.end());

    if (mode == 2) {
        int target = rnd.next(1, min<int>(static_cast<int>(candidates.size()), n + 3));
        edges.insert(edges.end(), candidates.begin(), candidates.begin() + target);
    } else {
        int target = rnd.next(max(1, n - 1), static_cast<int>(candidates.size()));
        edges.insert(edges.end(), candidates.begin(), candidates.begin() + target);
    }

    if (!edges.empty() && rnd.next(0, 2) == 0) {
        int duplicates = rnd.next(1, min(3, static_cast<int>(edges.size())));
        for (int i = 0; i < duplicates; ++i) {
            edges.push_back(rnd.any(edges));
        }
        shuffle(edges.begin(), edges.end());
    }

    return edges;
}

static vector<int> buildStones(int n, int mode) {
    vector<int> stones(n, 0);
    if (mode == 0) {
        stones[rnd.next(n)] = rnd.next(1, 5);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            stones[i] = rnd.next(0, 3);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            stones[i] = rnd.next(0, 20);
        }
        stones[rnd.next(n)] = rnd.next(100, 1000);
    }
    return stones;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tests = rnd.next(1, 5);
    int remainingN = 18;
    for (int tc = 0; tc < tests; ++tc) {
        int maxN = min(8, remainingN - (tests - tc - 1));
        int n = rnd.next(1, maxN);
        remainingN -= n;

        int graphMode = rnd.next(0, 3);
        int stoneMode = rnd.next(0, 2);
        vector<pair<int, int>> edges = buildEdges(n, graphMode);
        vector<int> stones = buildStones(n, stoneMode);
        printCase(n, edges, stones);
    }

    println(0, 0);
    return 0;
}
