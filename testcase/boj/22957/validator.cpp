#include "testlib.h"

using namespace std;

namespace {

const long long kMaxK = 9223372036854775807LL;

__int128 validCountWithLength(int length) {
    __int128 total = 1;
    for (int i = 0; i < length; ++i) {
        total *= 3;
    }

    __int128 allCountsEven = 0;
    if (length % 2 == 0) {
        allCountsEven = (total + 3) / 4;
    }
    return total - allCountsEven;
}

__int128 totalValidCount(int n) {
    __int128 result = 0;
    for (int length = 1; length <= n; ++length) {
        result += validCountWithLength(length);
    }
    return result;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 30, "N");
    inf.readSpace();
    long long k = inf.readLong(1LL, kMaxK, "K");
    inf.readEoln();
    inf.readEof();

    ensuref(totalValidCount(n) >= k, "the K-th valid number does not exist for N=%d, K=%lld", n, k);
}
