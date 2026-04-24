#include "testlib.h"
#include <vector>
using namespace std;

const int MAXN = 10000 + 5;
int parentDSU[MAXN];

int find_set(int v) {
    return parentDSU[v] == v ? v : (parentDSU[v] = find_set(parentDSU[v]));
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, T
    int n = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int m = inf.readInt(n - 1, 50000, "M");
    inf.readSpace();
    int T = inf.readInt(1, 10000, "T");
    inf.readEoln();

    // Initialize DSU
    for (int i = 1; i <= n; i++) {
        parentDSU[i] = i;
    }

    // Read cow counts
    vector<int> c = inf.readInts(n, 0, 10000, "c_i");
    inf.readEoln();

    // Read edges and union-find to check connectivity
    for (int i = 0; i < m; i++) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readSpace();
        int t = inf.readInt(1, 25000, "t_i");
        inf.readEoln();

        int pa = find_set(a);
        int pb = find_set(b);
        if (pa != pb) {
            parentDSU[pa] = pb;
        }
    }

    // Check connectivity: every field must connect to field 1
    for (int i = 1; i <= n; i++) {
        ensuref(find_set(i) == find_set(1),
                "Field %d is not connected to the barn (field 1)", i);
    }

    inf.readEof();
    return 0;
}
