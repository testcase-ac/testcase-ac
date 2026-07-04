#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 20, "N");
        inf.readSpace();
        int a = inf.readInt(1, 19, "A");
        inf.readSpace();
        int b = inf.readInt(a + 1, 20, "B");
        inf.readEoln();

        vector<int> u = inf.readInts(n, 0, 20, "U_i");
        inf.readEoln();

        ensuref(u.back() >= 1, "U_N must be at least 1");
        int total = accumulate(u.begin(), u.end(), 0);
        ensuref(total >= 2, "sum of U_i must be at least 2");
    }

    inf.readEof();
}
