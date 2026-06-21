#include "testlib.h"

#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, n - 1, "m");
    inf.readSpace();
    int k = inf.readInt(1, n - 1, "k");
    inf.readEoln();

    vector<bool> hasIron(n + 1, false);
    vector<bool> hasCoal(n + 1, false);

    for (int i = 0; i < m; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int ore = inf.readInt(1, n, "o_i");
        ensuref(!hasIron[ore], "duplicate iron cell: %d", ore);
        hasIron[ore] = true;
    }
    inf.readEoln();

    for (int i = 0; i < k; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int coal = inf.readInt(1, n, "c_i");
        ensuref(!hasCoal[coal], "duplicate coal cell: %d", coal);
        ensuref(!hasIron[coal], "cell contains both iron and coal: %d", coal);
        hasCoal[coal] = true;
    }
    inf.readEoln();

    for (int j = 1; j <= n; ++j) {
        int a = inf.readInt(0, 10, "a");
        set<int> neighbours;
        for (int i = 0; i < a; ++i) {
            inf.readSpace();
            int b = inf.readInt(1, n, "b_i");
            ensuref(b != j, "cell %d lists itself as an accessible neighbour", j);
            ensuref(neighbours.insert(b).second,
                    "cell %d has duplicate accessible neighbour %d", j, b);
        }
        inf.readEoln();
    }

    inf.readEof();
}
