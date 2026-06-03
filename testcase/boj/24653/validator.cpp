#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readEoln();

    vector<long long> s = inf.readLongs(n, 1LL, 1000000000LL, "s_i");
    inf.readEoln();

    long long t = inf.readLong(2LL, 1000000000LL, "t");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        ensuref(s[i] % t != 0, "s_%d must not be divisible by t: s_%d=%lld, t=%lld",
                i + 1, i + 1, s[i], t);
    }

    inf.readEof();
}
