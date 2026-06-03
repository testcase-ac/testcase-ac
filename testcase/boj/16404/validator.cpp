#include "testlib.h"
#include <queue>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 100000;
    const int MAX_M = 100000;
    const int MAX_W = 10000;

    int n = inf.readInt(1, MAX_N, "N");
    inf.readSpace();
    int m = inf.readInt(1, MAX_M, "M");
    inf.readEoln();

    vector<vector<int>> children(n + 1);
    for (int i = 1; i <= n; ++i) {
        int parent;
        if (i == 1) {
            parent = inf.readInt(-1, -1, "parent_1");
        } else {
            parent = inf.readInt(1, n, "parent_i");
            ensuref(parent != i, "employee %d cannot be their own supervisor", i);
            children[parent].push_back(i);
        }

        if (i == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    vector<int> visited(n + 1, 0);
    queue<int> q;
    visited[1] = 1;
    q.push(1);
    int reachable = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        ++reachable;
        for (int next : children[cur]) {
            ensuref(!visited[next], "employee %d is reached more than once", next);
            visited[next] = 1;
            q.push(next);
        }
    }
    ensuref(reachable == n, "the supervisor list must form one hierarchy rooted at employee 1");

    for (int command = 1; command <= m; ++command) {
        int type = inf.readInt(1, 2, "command_type");
        inf.readSpace();
        int employee = inf.readInt(1, n, "i");

        if (type == 1) {
            inf.readSpace();
            inf.readInt(-MAX_W, MAX_W, "w");
        }
        inf.readEoln();
    }

    inf.readEof();
}
