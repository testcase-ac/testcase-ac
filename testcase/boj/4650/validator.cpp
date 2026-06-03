#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

struct DSU {
    vector<int> parent;

    explicit DSU(int n) : parent(n) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            parent[b] = a;
        }
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int datasets = 0;
    while (true) {
        int n = inf.readInt(0, 26, "n");
        inf.readEoln();

        if (n == 0) {
            ensuref(datasets >= 1, "input must contain at least one data set");
            break;
        }
        ++datasets;
        ensuref(datasets <= 100, "too many data sets: %d", datasets);
        ensuref(n > 1, "non-final n must satisfy 1 < n < 27, got %d", n);

        DSU dsu(n);
        set<pair<int, int>> roads;
        vector<int> degree(n, 0);

        for (int i = 0; i < n - 1; ++i) {
            string from_label = inf.readToken("[A-Z]", "from_label");
            ensuref(from_label[0] == char('A' + i),
                    "expected row label %c, got %c", char('A' + i), from_label[0]);
            inf.readSpace();

            int k = inf.readInt(0, 15, "k");
            ensuref(k <= n - i - 1,
                    "row %c has %d roads, but only %d later villages exist",
                    char('A' + i), k, n - i - 1);

            set<int> row_targets;
            for (int j = 0; j < k; ++j) {
                inf.readSpace();
                string to_label = inf.readToken("[A-Z]", "to_label");
                int to = to_label[0] - 'A';
                ensuref(i < to && to < n,
                        "road from %c must go to a later village among the first %d labels, got %c",
                        char('A' + i), n, to_label[0]);
                ensuref(row_targets.insert(to).second,
                        "duplicate road target %c in row %c", to_label[0], char('A' + i));

                inf.readSpace();
                inf.readInt(1, 99, "cost");

                ensuref(roads.insert({i, to}).second,
                        "duplicate road between %c and %c", char('A' + i), to_label[0]);
                ++degree[i];
                ++degree[to];
                dsu.unite(i, to);
            }
            inf.readEoln();
        }

        ensuref((int)roads.size() <= 75, "road network has %d roads", (int)roads.size());
        for (int i = 0; i < n; ++i) {
            ensuref(degree[i] <= 15, "village %c has degree %d", char('A' + i), degree[i]);
        }

        int root = dsu.find(0);
        for (int i = 1; i < n; ++i) {
            ensuref(dsu.find(i) == root, "road network is not connected; village %c is unreachable", char('A' + i));
        }
    }

    inf.readEof();
    return 0;
}
