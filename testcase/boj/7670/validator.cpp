#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no case-count bound, so use the local default.
    const int MAX_CASES = 100000;
    int cases = 0;

    while (true) {
        int d = inf.readInt(0, 13, "d");
        if (d == 0) {
            inf.readEoln();
            break;
        }

        ++cases;
        ensuref(cases <= MAX_CASES, "number of cases exceeds %d", MAX_CASES);

        for (int i = 1; i <= d; ++i) {
            inf.readSpace();
            inf.readToken("d4|d6|d8|d10|d12|d20", "die");
        }

        inf.readSpace();
        inf.readInt(0, 1000, "x");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
