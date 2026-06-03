#include "testlib.h"

#include <queue>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    vector<vector<int>> children(n + 1);
    vector<int> parent(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }

        int low = (i == 1 ? 0 : 1);
        parent[i] = inf.readInt(low, n, "parent_i");
        if (i == 1) {
            ensuref(parent[i] == 0, "employee 1 must be the representative with parent 0");
        } else {
            ensuref(parent[i] != i, "employee %d cannot be their own superior", i);
            children[parent[i]].push_back(i);
        }
    }
    inf.readEoln();

    vector<int> seen(n + 1, 0);
    queue<int> q;
    q.push(1);
    seen[1] = 1;
    int reachable = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        ++reachable;

        for (int next : children[v]) {
            ensuref(!seen[next], "employee %d is reachable more than once", next);
            seen[next] = 1;
            q.push(next);
        }
    }
    ensuref(reachable == n, "organization must be rooted at employee 1; reached %d of %d employees", reachable, n);

    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    for (int query = 1; query <= m; ++query) {
        int type = inf.readInt(1, 3, "query_type");
        inf.readSpace();
        int employee = inf.readInt(1, n, "employee");
        inf.readEoln();

        (void)type;
        (void)employee;
    }

    inf.readEof();
}
