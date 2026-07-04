#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCase = 0;
    while (!inf.seekEof()) {
        ++testCase;
        setTestCase(testCase);

        int n = inf.readInt(1, 300, "N");
        inf.readEoln();

        for (int i = 1; i <= 2 * n - 1; ++i) {
            string row = inf.readLine("[HV]{" + to_string(n) + "}", "barrier_row");
            ensuref((int)row.size() == n,
                    "barrier row %d has length %d, expected %d",
                    i,
                    (int)row.size(),
                    n);
        }
    }

    ensuref(testCase >= 1, "input must contain at least one test case");
    inf.readEof();
}
