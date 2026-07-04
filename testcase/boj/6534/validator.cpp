#include "testlib.h"

#include <queue>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int kMaxPackagesPerDisc = 50000;
    constexpr int kMaxDependencies = 100000;
    constexpr int kMaxTotalWork = 200000;

    int caseIndex = 0;
    int totalWork = 0;
    while (true) {
        int n1 = inf.readInt(0, kMaxPackagesPerDisc, "N_1");
        inf.readSpace();
        int n2 = inf.readInt(0, kMaxPackagesPerDisc, "N_2");
        inf.readSpace();
        int d = inf.readInt(0, kMaxDependencies, "D");
        inf.readEoln();

        if (n1 == 0 && n2 == 0 && d == 0) {
            break;
        }

        ++caseIndex;
        setTestCase(caseIndex);
        ensuref(n1 >= 1, "N_1 must be positive in a non-terminal test case");
        ensuref(n2 >= 1, "N_2 must be positive in a non-terminal test case");

        int n = n1 + n2;
        // CHECK: The statement has no aggregate bound for several test cases; cap
        // the total scalar workload at one maximum-sized case for local validation.
        totalWork += n + d;
        ensuref(totalWork <= kMaxTotalWork,
                "total package/dependency workload exceeds %d", kMaxTotalWork);

        vector<vector<int>> graph(n + 1);
        vector<int> indegree(n + 1, 0);
        for (int i = 1; i <= d; ++i) {
            int x = inf.readInt(1, n, "x_i");
            inf.readSpace();
            int y = inf.readInt(1, n, "y_i");
            inf.readEoln();

            graph[y].push_back(x);
            ++indegree[x];
        }

        queue<int> ready;
        for (int package = 1; package <= n; ++package) {
            if (indegree[package] == 0) {
                ready.push(package);
            }
        }

        int visited = 0;
        while (!ready.empty()) {
            int package = ready.front();
            ready.pop();
            ++visited;
            for (int next : graph[package]) {
                --indegree[next];
                if (indegree[next] == 0) {
                    ready.push(next);
                }
            }
        }

        ensuref(visited == n, "dependence specifications contain a cycle");
    }

    ensuref(caseIndex >= 1, "input must contain at least one test case");
    inf.readEof();
}
