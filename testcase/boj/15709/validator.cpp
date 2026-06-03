#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 10000, "M");
    inf.readSpace();
    int bridgeCount = inf.readInt(1, 100, "B");
    inf.readSpace();
    int k = inf.readInt(1, 20000, "K");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    int totalNodes = n + m + bridgeCount;
    for (int i = 1; i <= k; ++i) {
        int a = inf.readInt(1, totalNodes, "a");
        inf.readSpace();
        int b = inf.readInt(1, totalNodes, "b");
        inf.readSpace();
        inf.readInt(1, 1000000000, "K_i");
        inf.readEoln();

        bool aHouse = a <= n;
        bool bHouse = b <= n;
        bool aHospital = n < a && a <= n + m;
        bool bHospital = n < b && b <= n + m;
        ensuref(!((aHouse && bHospital) || (aHospital && bHouse)),
                "road %d directly connects house and hospital: %d %d", i, a, b);
        // CHECK: the statement does not forbid self-loops or duplicate roads, so they are accepted.
    }

    for (int i = 1; i <= q; ++i) {
        inf.readInt(1, n, "S_i");
        inf.readSpace();
        inf.readInt(n + 1, n + m, "E_i");
        inf.readEoln();
    }

    inf.readEof();
}
