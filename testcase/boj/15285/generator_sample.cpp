#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct CaseData {
    int n;
    vector<pair<int, int>> edges;
};

void addEdge(set<pair<int, int>>& used, vector<pair<int, int>>& edges, int from, int to) {
    if (from == to || used.count({from, to})) {
        return;
    }
    used.insert({from, to});
    edges.push_back({from, to});
}

CaseData makeCase(int n, int mode) {
    set<pair<int, int>> used;
    vector<pair<int, int>> edges;

    for (int i = 1; i <= n; ++i) {
        int next = i == n ? 1 : i + 1;
        addEdge(used, edges, i, next);
        addEdge(used, edges, next, i);
    }

    if (mode == 0) {
        for (int i = 1; i <= n; ++i) {
            addEdge(used, edges, i, ((i + 1) % n) + 1);
        }
    } else if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            addEdge(used, edges, 1, i);
            addEdge(used, edges, i, 1);
        }
    } else {
        for (int gap = 2; gap < n; ++gap) {
            for (int i = 1; i <= n; ++i) {
                addEdge(used, edges, i, ((i + gap - 1) % n) + 1);
            }
        }
    }

    vector<pair<int, int>> candidates;
    for (int from = 1; from <= n; ++from) {
        for (int to = 1; to <= n; ++to) {
            if (from != to && !used.count({from, to})) {
                candidates.push_back({from, to});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int maximumEdges = n * (n - 1);
    int target = rnd.next(2 * n + 1, min(maximumEdges, 2 * n + 1 + rnd.next(0, n)));
    for (pair<int, int> edge : candidates) {
        if (static_cast<int>(edges.size()) >= target) {
            break;
        }
        addEdge(used, edges, edge.first, edge.second);
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());
    for (pair<int, int>& edge : edges) {
        edge = {label[edge.first], label[edge.second]};
    }
    shuffle(edges.begin(), edges.end());

    return {n, edges};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCount = rnd.next(1, 3);
    vector<CaseData> cases;
    for (int caseIndex = 0; caseIndex < testCount; ++caseIndex) {
        int n = rnd.next(4, 10);
        int mode = rnd.next(0, 2);
        cases.push_back(makeCase(n, mode));
    }

    println(testCount);
    for (const CaseData& testCase : cases) {
        println(testCase.n, static_cast<int>(testCase.edges.size()));
        for (pair<int, int> edge : testCase.edges) {
            println(edge.first, edge.second);
        }
    }

    return 0;
}
