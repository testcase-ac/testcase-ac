#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Operation {
    int type;
    int x;
    int y;
};

static long long edgeKey(int u, int v) {
    return (static_cast<long long>(u) << 32) | static_cast<unsigned int>(v);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tests = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long totalK = 0;
    long long totalN = 0;
    long long totalM = 0;

    for (int tc = 1; tc <= tests; ++tc) {
        setTestCase(tc);

        int k = inf.readInt(1, 100000, "k");
        inf.readSpace();
        int n = inf.readInt(1, 100000, "n");
        inf.readSpace();
        int maxEdges = min(100000LL, 1LL * n * (n - 1) / 2);
        int m = inf.readInt(0, maxEdges, "m");
        inf.readEoln();

        totalK += k;
        totalN += n;
        totalM += m;
        ensuref(totalK <= 100000, "sum of k exceeds 100000");
        ensuref(totalN <= 100000, "sum of n exceeds 100000");
        ensuref(totalM <= 100000, "sum of m exceeds 100000");

        set<long long> currentEdges;
        for (int i = 1; i <= m; ++i) {
            int u = inf.readInt(1, n, "u");
            inf.readSpace();
            int v = inf.readInt(u + 1, n, "v");
            inf.readEoln();

            long long key = edgeKey(u, v);
            ensuref(currentEdges.insert(key).second,
                    "duplicate initial edge at index %d: (%d, %d)",
                    i,
                    u,
                    v);
        }

        vector<Operation> op(k + 1);
        vector<vector<int>> children(k + 1);
        for (int i = 2; i <= k; ++i) {
            int p = inf.readInt(1, i - 1, "p_i");
            inf.readSpace();
            string type = inf.readToken("add|remove", "t_i");
            inf.readSpace();
            int x = inf.readInt(1, n, "x_i");
            inf.readSpace();
            int y = inf.readInt(x + 1, n, "y_i");
            inf.readEoln();

            op[i] = {type == "add" ? 1 : -1, x, y};
            children[p].push_back(i);
        }

        vector<pair<int, int>> stack;
        stack.push_back({1, 0});
        while (!stack.empty()) {
            int graph = stack.back().first;
            int& childIndex = stack.back().second;

            if (childIndex == static_cast<int>(children[graph].size())) {
                if (graph != 1) {
                    long long key = edgeKey(op[graph].x, op[graph].y);
                    if (op[graph].type == 1) {
                        currentEdges.erase(key);
                    } else {
                        currentEdges.insert(key);
                    }
                }
                stack.pop_back();
                continue;
            }

            int child = children[graph][childIndex++];
            long long key = edgeKey(op[child].x, op[child].y);
            bool exists = currentEdges.count(key) != 0;
            if (op[child].type == 1) {
                ensuref(!exists,
                        "graph %d adds existing edge (%d, %d) from parent %d",
                        child,
                        op[child].x,
                        op[child].y,
                        graph);
                currentEdges.insert(key);
            } else {
                ensuref(exists,
                        "graph %d removes missing edge (%d, %d) from parent %d",
                        child,
                        op[child].x,
                        op[child].y,
                        graph);
                currentEdges.erase(key);
            }
            stack.push_back({child, 0});
        }
    }

    inf.readEof();
}
