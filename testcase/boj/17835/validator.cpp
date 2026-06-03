#include "testlib.h"

#include <queue>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 500000, "m");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();

    vector<vector<int>> reverseGraph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        inf.readInt(1, 100000, "c");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge %d: %d -> %d", i + 1, u, v);
        reverseGraph[v].push_back(u);
    }

    vector<bool> isInterviewCity(n + 1, false);
    queue<int> q;
    for (int i = 0; i < k; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int city = inf.readInt(1, n, "interview_city");
        ensuref(!isInterviewCity[city], "duplicate interview city: %d", city);
        isInterviewCity[city] = true;
        q.push(city);
    }
    inf.readEoln();

    vector<bool> canReachInterview(n + 1, false);
    while (!q.empty()) {
        int city = q.front();
        q.pop();
        if (canReachInterview[city]) {
            continue;
        }
        canReachInterview[city] = true;
        for (int previous : reverseGraph[city]) {
            if (!canReachInterview[previous]) {
                q.push(previous);
            }
        }
    }

    for (int city = 1; city <= n; ++city) {
        ensuref(canReachInterview[city],
                "city %d cannot reach any interview city",
                city);
    }

    inf.readEof();
}
