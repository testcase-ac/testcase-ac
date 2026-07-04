#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(2, 1000, "K");
    inf.readSpace();
    int n = inf.readInt(1, 50000, "N");
    inf.readEoln();

    vector<vector<int>> graph(k + 1);
    set<pair<int, int>> elevators;
    for (int i = 1; i <= n; ++i) {
        int a = inf.readInt(1, k - 1, "A");
        inf.readSpace();
        int b = inf.readInt(a + 1, k, "B");
        inf.readEoln();

        ensuref(elevators.insert({a, b}).second,
                "duplicate elevator at line %d: (%d, %d)", i + 1, a, b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> stack = {1};
    vector<char> seen(k + 1, 0);
    seen[1] = 1;
    while (!stack.empty()) {
        int floor = stack.back();
        stack.pop_back();
        for (int next : graph[floor]) {
            if (!seen[next]) {
                seen[next] = 1;
                stack.push_back(next);
            }
        }
    }
    ensuref(seen[k], "floor %d is not reachable from floor 1", k);

    inf.readEof();
}
