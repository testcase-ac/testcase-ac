#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readSpace();
    long long a = inf.readLong(1LL, 10000000000LL, "A");
    inf.readEoln();

    vector<int> s = inf.readInts(n, 1, 100000, "s_i");
    inf.readEoln();

    int maxScore = *max_element(s.begin(), s.end());
    ensuref(a <= 1LL * m * maxScore,
            "promotion must be possible: A=%lld, M=%d, max_s=%d",
            a, m, maxScore);

    inf.readEof();
}
