#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and H
    int N = inf.readInt(1, 20, "N");
    inf.readSpace();
    long long H = inf.readLong(1LL, 1000000000LL, "H");
    inf.readEoln();

    // Read adjacency matrix rows
    vector<string> a(N);
    for (int i = 0; i < N; i++) {
        // Each row must be a string of '0'/'1', length between 1 and 20
        string s = inf.readLine("[01]{1,20}", "row");
        ensuref((int)s.size() == N,
                "Row %d has length %d, expected %d",
                i + 1, (int)s.size(), N);
        a[i] = s;
    }

    // Validate no self-friendship and symmetry
    for (int i = 0; i < N; i++) {
        // Diagonal must be '0'
        ensuref(a[i][i] == '0',
                "Diagonal element at (%d,%d) is '%c', expected '0'",
                i + 1, i + 1, a[i][i]);
        // Symmetry: a[i][j] == a[j][i]
        for (int j = i + 1; j < N; j++) {
            ensuref(a[i][j] == a[j][i],
                    "Matrix not symmetric at (%d,%d)='%c' and (%d,%d)='%c'",
                    i + 1, j + 1, a[i][j],
                    j + 1, i + 1, a[j][i]);
        }
    }

    inf.readEof();
    return 0;
}
