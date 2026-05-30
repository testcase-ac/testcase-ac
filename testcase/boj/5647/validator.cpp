#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long Q_MIN = 0LL;
    const long long Q_MAX = 99999999999999LL;
    const int MAX_TESTS = 2000;

    int testCount = 0;
    while (true) {
        long long q = inf.readLong(Q_MIN, Q_MAX, "q");
        inf.readEoln();

        if (q == 0) {
            break;
        }

        ++testCount;
        ensuref(testCount <= MAX_TESTS,
                "Number of input cases exceeds %d", MAX_TESTS);
    }

    inf.readEof();
}
