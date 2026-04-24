#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: n, m
    int n = inf.readInt(1, 500000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 500000, "m");
    inf.readEoln();

    // Second line: c1, c2
    int c1 = inf.readInt(-100000000, 100000000, "c1");
    inf.readSpace();
    int c2 = inf.readInt(-100000000, 100000000, "c2");
    inf.readEoln();

    // Third line: x-coordinates of P
    vector<int> P(n);
    for (int i = 0; i < n; i++) {
        if (i > 0) inf.readSpace();
        P[i] = inf.readInt(-100000000, 100000000, "x_P");
    }
    inf.readEoln();

    // Fourth line: x-coordinates of Q
    vector<int> Q(m);
    for (int i = 0; i < m; i++) {
        if (i > 0) inf.readSpace();
        Q[i] = inf.readInt(-100000000, 100000000, "x_Q");
    }
    inf.readEoln();

    // Check distinctness in P
    {
        vector<int> tmp = P;
        sort(tmp.begin(), tmp.end());
        for (int i = 1; i < n; i++) {
            ensuref(tmp[i] != tmp[i-1],
                    "Duplicate x-coordinate in P: %d appears twice", tmp[i]);
        }
    }

    // Check distinctness in Q
    {
        vector<int> tmp = Q;
        sort(tmp.begin(), tmp.end());
        for (int i = 1; i < m; i++) {
            ensuref(tmp[i] != tmp[i-1],
                    "Duplicate x-coordinate in Q: %d appears twice", tmp[i]);
        }
    }

    inf.readEof();
    return 0;
}
