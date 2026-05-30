#include "testlib.h"
using namespace std;

int readFlexibleInt(int minValue, int maxValue, const string& name) {
    inf.skipBlanks();
    return inf.readInt(minValue, maxValue, name);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = 0;
    while (true) {
        inf.skipBlanks();
        if (inf.eof()) {
            break;
        }

        setTestCase(++tc);
        ensuref(tc <= 100000, "Number of test cases exceeds 100000: %d", tc);

        // CHECK: The statement only writes N <= 100000, but a data set length of 0 would have no stock sequence.
        int n = inf.readInt(1, 100000, "N");

        for (int i = 0; i < n; ++i) {
            readFlexibleInt(1, 100000, "price");
        }
    }

    inf.skipBlanks();
    ensuref(tc > 0, "input must contain at least one data set");
    inf.readEof();
    return 0;
}
