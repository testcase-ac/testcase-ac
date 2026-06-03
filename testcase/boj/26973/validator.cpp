#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    long long totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "N");
        inf.readEoln();

        totalN += n;
        ensuref(totalN <= 200000, "sum of N exceeds 200000 after test case %d", tc);

        vector<int> a = inf.readInts(n, 1, 5000000, "a_i");
        inf.readEoln();
    }

    inf.readEof();
}
