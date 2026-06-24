#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long n;
int requiredLength;

int minRequiredLength(long long value) {
    int low = 0;
    int high = 1000000;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if ((__int128)9 * mid * mid >= (__int128)4 * value) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

struct Answer {
    int k;
};

Answer readAnswer(InStream& stream) {
    int k = stream.readInt(requiredLength, 1000000, "k");
    stream.readEoln();
    vector<long long> a(k);

    for (int i = 0; i < k; ++i) {
        a[i] = stream.readLong(1, n, format("a[%d]", i + 1).c_str());
    }
    stream.readEoln();
    stream.readEof();

    for (int i = 1; i < k; ++i) {
        if (a[i] <= a[i - 1]) {
            stream.quitf(_wa,
                         "sequence is not strictly increasing at a[%d]=%lld, a[%d]=%lld",
                         i, a[i - 1], i + 1, a[i]);
        }
    }

    long long previousGcd = 0;
    for (int i = 1; i < k; ++i) {
        long long currentGcd = __gcd(a[i], a[i - 1]);
        if (i >= 2 && currentGcd <= previousGcd) {
            stream.quitf(_wa,
                         "gcd condition fails at positions %d,%d,%d: previous=%lld current=%lld",
                         i - 1, i, i + 1, previousGcd, currentGcd);
        }
        previousGcd = currentGcd;
    }

    return {k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readLong(1, 1000000000000LL, "n");
    inf.readEoln();
    inf.readEof();
    requiredLength = minRequiredLength(n);

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    quitf(_ok, "valid BSU of length %d, jury length %d", participant.k, jury.k);
}
