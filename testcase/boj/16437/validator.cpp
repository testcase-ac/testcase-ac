#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 123456, "N");
    inf.readEoln();

    vector<int> parent(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        string t = inf.readToken("[SW]", "t_i");
        inf.readSpace();
        long long a = inf.readLong(1LL, 1000000000LL, "a_i");
        inf.readSpace();
        int p = inf.readInt(1, n, "p_i");
        inf.readEoln();

        (void)t;
        (void)a;
        parent[i] = p;
    }

    vector<int> state(n + 1, 0);
    state[1] = 2;

    for (int start = 2; start <= n; ++start) {
        if (state[start] == 2) {
            continue;
        }

        vector<int> path;
        int cur = start;
        while (state[cur] == 0) {
            state[cur] = 1;
            path.push_back(cur);
            cur = parent[cur];
        }

        ensuref(state[cur] == 2,
                "island %d does not have a route ending at island 1", start);

        for (int node : path) {
            state[node] = 2;
        }
    }

    inf.readEof();
}
