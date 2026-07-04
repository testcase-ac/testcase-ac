#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>
using namespace std;

class AllianceState {
public:
    explicit AllianceState(int n) : parent_(n + 1), size_(n + 1, 1), enemies_(n + 1) {
        for (int i = 1; i <= n; ++i) {
            parent_[i] = i;
        }
    }

    int find(int x) {
        if (parent_[x] == x) {
            return x;
        }
        return parent_[x] = find(parent_[x]);
    }

    void addDistrust(int a, int b) {
        enemies_[a].insert(b);
        enemies_[b].insert(a);
    }

    bool canMerge(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        ensuref(ra != rb, "proposal joins one current state: (%d, %d)", a, b);

        if (enemies_[ra].size() > enemies_[rb].size()) {
            swap(ra, rb);
        }
        for (int enemy : enemies_[ra]) {
            if (find(enemy) == rb) {
                return false;
            }
        }
        return true;
    }

    void merge(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra == rb) {
            return;
        }
        if (size_[ra] < size_[rb]) {
            swap(ra, rb);
        }

        parent_[rb] = ra;
        size_[ra] += size_[rb];

        vector<int> oldEnemies(enemies_[rb].begin(), enemies_[rb].end());
        for (int enemy : oldEnemies) {
            int re = find(enemy);
            enemies_[re].erase(rb);
            if (re != ra) {
                enemies_[re].insert(ra);
                enemies_[ra].insert(re);
            }
        }
        enemies_[rb].clear();
    }

private:
    vector<int> parent_;
    vector<int> size_;
    vector<set<int>> enemies_;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    AllianceState state(n);
    set<pair<int, int>> distrustPairs;
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        ensuref(u != v, "distrust pair %d is a self-loop: (%d, %d)", i, u, v);
        auto normalized = minmax(u, v);
        ensuref(distrustPairs.insert(normalized).second,
                "duplicate distrust pair %d: (%d, %d)", i, u, v);
        state.addDistrust(u, v);
    }

    for (int i = 1; i <= q; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        if (state.canMerge(a, b)) {
            state.merge(a, b);
        }
    }

    inf.readEof();
}
