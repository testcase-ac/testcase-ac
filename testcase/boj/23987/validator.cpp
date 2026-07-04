#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    int hugeCases = 0;
    for (int caseIdx = 1; caseIdx <= t; ++caseIdx) {
        setTestCase(caseIdx);

        int n = inf.readInt(2, 5000000, "N");
        inf.readEoln();

        // CHECK: The statement has either all-small cases or one N=5000000
        // large case with the remaining cases small.
        ensuref(n <= 100 || n == 5000000,
                "N must be in [2, 100] or equal to 5000000, got %d", n);
        if (n == 5000000) {
            ++hugeCases;
            ensuref(hugeCases <= 1, "more than one case has N=5000000");
        }

        string scores = inf.readToken("[0-9]{" + to_string(n) + "}", "scores");
        inf.readEoln();
    }

    inf.readEof();
}
