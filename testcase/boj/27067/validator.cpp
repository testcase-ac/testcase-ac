#include "testlib.h"

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

bool isPermutation(const vector<int>& values, int n) {
    vector<int> seen(n + 1, 0);
    for (int value : values) {
        if (seen[value]) return false;
        seen[value] = 1;
    }
    return true;
}

void addFirstMismatchCandidates(const vector<int>& lhs, const vector<int>& rhs, vector<int>& candidates) {
    int n = (int)lhs.size();
    for (int i = 0; i < n; ++i) {
        if (lhs[i] != rhs[i]) {
            candidates.push_back(lhs[i]);
            candidates.push_back(rhs[i]);
            return;
        }
    }
}

bool isForwardMoveFrom(const vector<int>& original, const vector<int>& transformed, int& moved) {
    int n = (int)original.size();
    int first = 0;
    while (first < n && original[first] == transformed[first]) ++first;
    if (first == n) return false;

    moved = transformed[first];
    vector<int> originalWithout;
    vector<int> transformedWithout;
    originalWithout.reserve(n - 1);
    transformedWithout.reserve(n - 1);

    int originalPos = -1;
    int transformedPos = -1;
    for (int i = 0; i < n; ++i) {
        if (original[i] == moved) {
            originalPos = i;
        } else {
            originalWithout.push_back(original[i]);
        }

        if (transformed[i] == moved) {
            transformedPos = i;
        } else {
            transformedWithout.push_back(transformed[i]);
        }
    }

    return transformedPos < originalPos && originalWithout == transformedWithout;
}

vector<int> insertMovedLater(const vector<int>& transformed, int moved, int originalPos) {
    int n = (int)transformed.size();
    vector<int> withoutMoved;
    withoutMoved.reserve(n - 1);
    for (int value : transformed) {
        if (value != moved) withoutMoved.push_back(value);
    }

    vector<int> original;
    original.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (i == originalPos) original.push_back(moved);
        if (i < n - 1) original.push_back(withoutMoved[i]);
    }
    return original;
}

vector<int> withoutValue(const vector<int>& values, int removed) {
    vector<int> result;
    result.reserve(values.size() - 1);
    for (int value : values) {
        if (value != removed) result.push_back(value);
    }
    return result;
}

vector<int> withoutTwoValues(const vector<int>& values, int firstRemoved, int secondRemoved) {
    vector<int> result;
    result.reserve(values.size() - 2);
    for (int value : values) {
        if (value != firstRemoved && value != secondRemoved) result.push_back(value);
    }
    return result;
}

bool firstDifferentValueAfterRemoval(const vector<int>& lhs, const vector<int>& rhs, int removed, int& value) {
    vector<int> lhsWithout = withoutValue(lhs, removed);
    vector<int> rhsWithout = withoutValue(rhs, removed);
    for (int i = 0; i < (int)lhsWithout.size(); ++i) {
        if (lhsWithout[i] != rhsWithout[i]) {
            value = rhsWithout[i];
            return true;
        }
    }
    return false;
}

vector<int> topologicalOrderWithPreference(
        const vector<int>& a,
        const vector<int>& b,
        const vector<int>& c,
        int movedA,
        int movedB,
        int movedC,
        const vector<int>& preference) {
    int n = (int)a.size();
    vector<int> rank(n + 1);
    for (int i = 0; i < n; ++i) rank[preference[i]] = i;

    vector<pair<int, int>> edges;
    auto addEdges = [&](const vector<int>& values, int removed) {
        vector<int> kept = withoutValue(values, removed);
        for (int i = 0; i + 1 < (int)kept.size(); ++i) {
            edges.push_back({kept[i], kept[i + 1]});
        }
    };

    addEdges(a, movedA);
    addEdges(b, movedB);
    addEdges(c, movedC);

    sort(edges.begin(), edges.end());
    edges.erase(unique(edges.begin(), edges.end()), edges.end());

    vector<vector<int>> graph(n + 1);
    vector<int> indegree(n + 1, 0);
    for (auto [from, to] : edges) {
        graph[from].push_back(to);
        ++indegree[to];
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> available;
    for (int value = 1; value <= n; ++value) {
        if (indegree[value] == 0) available.push({rank[value], value});
    }

    vector<int> order;
    order.reserve(n);
    while (!available.empty()) {
        int value = available.top().second;
        available.pop();
        order.push_back(value);
        for (int next : graph[value]) {
            --indegree[next];
            if (indegree[next] == 0) available.push({rank[next], next});
        }
    }

    if ((int)order.size() != n) return {};
    return order;
}

bool tryMovedTriple(
        const vector<int>& a,
        const vector<int>& b,
        const vector<int>& c,
        int movedA,
        int movedB,
        int movedC) {
    if (movedA == 0 || movedB == 0 || movedC == 0) return false;
    if (movedA == movedB || movedA == movedC || movedB == movedC) return false;
    if (withoutTwoValues(a, movedA, movedC) != withoutTwoValues(c, movedA, movedC)) return false;

    vector<vector<int>> preferences = {a, b, c};
    vector<int> numeric(a.size());
    for (int i = 0; i < (int)numeric.size(); ++i) numeric[i] = i + 1;
    preferences.push_back(numeric);

    for (const vector<int>& preference : preferences) {
        vector<int> original = topologicalOrderWithPreference(a, b, c, movedA, movedB, movedC, preference);
        if (original.empty()) continue;

        int actualA = -1;
        int actualB = -1;
        int actualC = -1;
        if (!isForwardMoveFrom(original, a, actualA)) continue;
        if (!isForwardMoveFrom(original, b, actualB)) continue;
        if (!isForwardMoveFrom(original, c, actualC)) continue;
        if (actualA == movedA && actualB == movedB && actualC == movedC) return true;
    }

    return false;
}

bool hasValidRestoration(const vector<int>& a, const vector<int>& b, const vector<int>& c, int n) {
    for (int i = 0; i < n; ++i) {
        if (a[i] == b[i]) continue;

        int movedA = a[i];
        int movedB = 0;
        int movedC = 0;
        if (firstDifferentValueAfterRemoval(a, b, movedA, movedB) &&
            firstDifferentValueAfterRemoval(b, c, movedB, movedC) &&
            tryMovedTriple(a, b, c, movedA, movedB, movedC)) {
            return true;
        }

        movedA = 0;
        movedB = b[i];
        movedC = 0;
        if (firstDifferentValueAfterRemoval(b, a, movedB, movedA) &&
            firstDifferentValueAfterRemoval(a, c, movedA, movedC) &&
            tryMovedTriple(a, b, c, movedA, movedB, movedC)) {
            return true;
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 3000, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, n, "A_i");
    inf.readEoln();
    vector<int> b = inf.readInts(n, 1, n, "B_i");
    inf.readEoln();
    vector<int> c = inf.readInts(n, 1, n, "C_i");
    inf.readEoln();
    inf.readEof();

    ensuref(isPermutation(a, n), "A must be a permutation of 1..N");
    ensuref(isPermutation(b, n), "B must be a permutation of 1..N");
    ensuref(isPermutation(c, n), "C must be a permutation of 1..N");
    ensuref(hasValidRestoration(a, b, c, n),
            "no original ordering can produce A, B, and C by three distinct forward moves");
}
