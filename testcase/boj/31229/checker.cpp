#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int n;

void readAnswer(InStream& stream) {
    vector<long long> a(n);
    set<long long> used;

    for (int i = 0; i < n; ++i) {
        a[i] = stream.readLong(1, 1000000000LL, format("A[%d]", i + 1).c_str());
        if (!used.insert(a[i]).second) {
            stream.quitf(_wa, "A[%d]=%lld is repeated", i + 1, a[i]);
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after sequence");
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long long sum = a[i] + a[j];
            __int128 product = static_cast<__int128>(a[i]) * a[j];
            if (product % sum == 0) {
                stream.quitf(_wa,
                             "A[%d]+A[%d]=%lld divides A[%d]*A[%d]",
                             i + 1,
                             j + 1,
                             sum,
                             i + 1,
                             j + 1);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 5000, "N");

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid sequence of length %d", n);
}
