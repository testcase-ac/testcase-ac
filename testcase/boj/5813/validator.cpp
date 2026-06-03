#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

namespace {

const int MAX_N = 100000;
const int MAX_COORD = 2147483646;

struct Dsu {
    vector<int> parent;
    vector<int> size;

    explicit Dsu(int n) : parent(n), size(n, 1) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives only upper bounds in subtasks; N blocks make
    // an empty city undefined, so this validator requires at least one block.
    int n = inf.readInt(1, MAX_N, "N");
    inf.readEoln();

    vector<pair<int, int> > cells(n);
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(1, MAX_COORD, "X_i");
        inf.readSpace();
        int y = inf.readInt(1, MAX_COORD, "Y_i");
        inf.readEoln();
        cells[i] = make_pair(x, y);
    }
    inf.readEof();

    sort(cells.begin(), cells.end());
    for (int i = 1; i < n; ++i) {
        ensuref(cells[i - 1] != cells[i], "duplicate block at (%d, %d)",
                cells[i].first, cells[i].second);
    }

    Dsu dsu(n);
    long long adjacentPairs = 0;
    set<pair<int, int> > vertices;

    for (int i = 0; i < n; ++i) {
        int x = cells[i].first;
        int y = cells[i].second;

        vertices.insert(make_pair(x, y));
        vertices.insert(make_pair(x + 1, y));
        vertices.insert(make_pair(x, y + 1));
        vertices.insert(make_pair(x + 1, y + 1));

        pair<int, int> left = make_pair(x, y - 1);
        pair<int, int> up = make_pair(x - 1, y);

        int leftIndex = int(lower_bound(cells.begin(), cells.end(), left) - cells.begin());
        if (leftIndex < n && cells[leftIndex] == left) {
            ++adjacentPairs;
            dsu.unite(i, leftIndex);
        }

        int upIndex = int(lower_bound(cells.begin(), cells.end(), up) - cells.begin());
        if (upIndex < n && cells[upIndex] == up) {
            ++adjacentPairs;
            dsu.unite(i, upIndex);
        }
    }

    int root = dsu.find(0);
    for (int i = 1; i < n; ++i) {
        ensuref(dsu.find(i) == root, "blocks are not connected");
    }

    long long edgeCount = 4LL * n - adjacentPairs;
    long long holeCount = 1LL - (long long)vertices.size() + edgeCount - n;
    ensuref(holeCount == 0, "city has %lld hole(s)", holeCount);
}
