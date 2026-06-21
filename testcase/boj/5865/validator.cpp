#include "testlib.h"

#include <queue>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "N");
    inf.readSpace();
    int m = inf.readInt(1, 500, "M");
    inf.readSpace();
    inf.readInt(1, 1000000, "X");
    inf.readEoln();

    vector<vector<int>> graph(n + 1);
    for (int edge = 1; edge <= m; ++edge) {
        int i = inf.readInt(1, n, "I");
        inf.readSpace();
        int j = inf.readInt(1, n, "J");
        inf.readSpace();
        inf.readInt(1, 1000000, "L");
        inf.readSpace();
        inf.readInt(1, 1000000, "C");
        inf.readEoln();

        graph[i].push_back(j);
        graph[j].push_back(i);
    }

    vector<bool> seen(n + 1, false);
    queue<int> q;
    seen[1] = true;
    q.push(1);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int next : graph[node]) {
            if (!seen[next]) {
                seen[next] = true;
                q.push(next);
            }
        }
    }

    // CHECK: The statement asks for the minimum over paths from 1 to N but does
    // not explicitly state connectivity; without such a path the answer is
    // undefined.
    ensuref(seen[n], "junction N must be reachable from junction 1");

    inf.readEof();
}
