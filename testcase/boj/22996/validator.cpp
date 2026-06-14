#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 300000, "Q");
    inf.readEoln();

    vector<int> par = inf.readInts(n, 1, n, "par_i");
    inf.readEoln();

    vector<int> state(n + 1, 0);
    int roots = 0;
    for (int start = 1; start <= n; ++start) {
        int v = start;
        while (state[v] == 0) {
            state[v] = start;
            v = par[v - 1];
        }
        ensuref(state[v] != start || par[v - 1] == v,
                "par array contains a directed cycle reaching vertex %d", v);

        v = start;
        while (state[v] == start) {
            state[v] = -1;
            v = par[v - 1];
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (par[i - 1] == i) {
            ++roots;
        }
    }

    int m = inf.readInt(1, q, "M");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        inf.readInt(1, n, "returned_i");
        inf.readEoln();
    }

    int type1_slots = q - m;
    int required_successful_merges = n - roots;
    ensuref(type1_slots >= required_successful_merges,
            "only %d type-1 queries are available, but final par needs at least %d successful merges",
            type1_slots, required_successful_merges);

    inf.readEof();
}
