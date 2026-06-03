#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 100000, "m");
    inf.readSpace();
    int k = inf.readInt(1, 100000, "k");
    inf.readEoln();

    vector<int> mentor(n + 1);
    for (int i = 1; i <= n; ++i) {
        mentor[i] = inf.readInt(-1, n, "mentor_i");
        ensuref(mentor[i] != 0, "mentor of student %d is 0", i);
        ensuref(mentor[i] != i, "student %d is their own mentor", i);
        if (i == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    vector<int> state(n + 1, 0);
    for (int start = 1; start <= n; ++start) {
        int v = start;
        while (v != -1 && state[v] == 0) {
            state[v] = start;
            v = mentor[v];
        }
        ensuref(v == -1 || state[v] != start, "mentor relation contains a cycle through student %d", start);

        v = start;
        while (v != -1 && state[v] == start) {
            state[v] = -1;
            v = mentor[v];
        }
    }

    for (int i = 1; i <= m; ++i) {
        inf.readInt(1, n, "x_i");
        inf.readEoln();
    }

    for (int i = 1; i <= k; ++i) {
        inf.readInt(0, m, "a_i");
        inf.readSpace();
        inf.readInt(1, n, "b_i");
        inf.readSpace();
        inf.readInt(1, n, "c_i");
        inf.readEoln();
    }

    inf.readEof();
}
