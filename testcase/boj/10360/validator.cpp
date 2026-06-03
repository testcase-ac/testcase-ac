#include "testlib.h"

#include <queue>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int case_id = 1; case_id <= t; ++case_id) {
        setTestCase(case_id);

        int n = inf.readInt(1, 1000, "N");
        inf.readSpace();
        int m = inf.readInt(0, 2000, "M");
        inf.readEoln();

        vector<vector<int>> graph(n);
        for (int i = 0; i < m; ++i) {
            int a = inf.readInt(0, n - 1, "A");
            inf.readSpace();
            int b = inf.readInt(0, n - 1, "B");
            inf.readSpace();
            int c = inf.readInt(-1000, 1000, "C");
            inf.readEoln();

            ensuref(a != b, "pool %d is a self-loop at mountain %d", i + 1, a);
            graph[a].push_back(b);
            (void)c;
        }

        vector<int> seen(n, 0);
        queue<int> q;
        seen[0] = 1;
        q.push(0);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int to : graph[v]) {
                if (!seen[to]) {
                    seen[to] = 1;
                    q.push(to);
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            ensuref(seen[i], "mountain %d is not reachable from mountain 0", i);
        }
    }

    inf.readEof();
}
