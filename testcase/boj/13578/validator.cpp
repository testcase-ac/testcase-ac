#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseIndex = 0;
    while (true) {
        int n = inf.readInt(0, 10000, "N");
        inf.readSpace();
        int j = inf.readInt(0, 20, "J");
        inf.readEoln();

        if (n == 0 && j == 0) {
            break;
        }

        ++caseIndex;
        setTestCase(caseIndex);

        ensuref(2 <= n, "N must be at least 2, got %d", n);
        ensuref(2 <= j, "J must be at least 2, got %d", j);
        ensuref(j <= n, "J must not exceed N, got J=%d and N=%d", j, n);

        for (int i = 0; i < n; ++i) {
            inf.readInt(1, 13, "card");
            if (i + 1 < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
    return 0;
}
