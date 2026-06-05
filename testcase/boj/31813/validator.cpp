#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<long long> pow10(18, 1);
    for (int i = 1; i <= 17; ++i) {
        pow10[i] = pow10[i - 1] * 10;
    }

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 17, "N");
        inf.readSpace();
        long long k = inf.readLong(pow10[n - 1], pow10[n] - 1, "K");
        inf.readEoln();

        ensuref(k >= pow10[n - 1] && k < pow10[n],
                "K must have exactly N digits: N=%d, K=%lld", n, k);
    }

    inf.readEof();
}
