#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readEoln();

    vector<int> parent(n + 1, 0);
    for (int employee = 2; employee <= n; ++employee) {
        if (employee > 2) {
            inf.readSpace();
        }
        parent[employee] = inf.readInt(1, n, "parent_i");
        ensuref(parent[employee] != employee,
                "employee %d cannot be their own supervisor", employee);
    }
    inf.readEoln();

    vector<int> state(n + 1, 0);
    state[1] = 2;
    for (int employee = 2; employee <= n; ++employee) {
        if (state[employee] == 2) {
            continue;
        }

        int current = employee;
        vector<int> path;
        while (state[current] == 0) {
            ensuref(current >= 2 && current <= n,
                    "employee %d does not reach president 1", employee);
            state[current] = 1;
            path.push_back(current);
            current = parent[current];
        }
        ensuref(state[current] == 2,
                "cycle detected while tracing employee %d", employee);
        for (int node : path) {
            state[node] = 2;
        }
    }

    for (int employee = 1; employee <= n; ++employee) {
        if (employee > 1) {
            inf.readSpace();
        }
        inf.readInt(0, 100, "A_i");
    }
    inf.readEoln();

    inf.readEof();
}
