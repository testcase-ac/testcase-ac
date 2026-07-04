#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr long long kMaxValue = 1000000000000000LL;

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000, "N");
        inf.readSpace();
        long long m = inf.readLong(0LL, kMaxValue, "M");
        inf.readEoln();

        vector<long long> a = inf.readLongs(n, 0LL, kMaxValue, "A_i");
        inf.readEoln();
    }

    inf.readEof();
}
