#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int n;

struct Answer {
    vector<long long> values;
};

Answer readAnswer(InStream& stream) {
    vector<long long> values(n + 1);
    set<long long> seen;
    long long sum = 0;

    for (int i = 0; i <= n; ++i) {
        values[i] = stream.readLong(-1000000000LL, 1000000000LL,
                                    format("A[%d]", i + 1).c_str());
        if (!seen.insert(values[i]).second) {
            stream.quitf(_wa, "A[%d]=%lld is repeated", i + 1, values[i]);
        }
        if (i < n) {
            sum += values[i];
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after A[%d]", n + 1);
    }

    long long target = values[n] * n;
    if (sum != target) {
        stream.quitf(_wa,
                     "average condition fails: sum of first N values is %lld, but N*A[N+1] is %lld",
                     sum, target);
    }

    return {values};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 10000, "N");

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid sequence of %d distinct integers", n + 1);
}
