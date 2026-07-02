#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

using int64 = long long;
using i128 = __int128_t;

const int64 MAX_N = 1000000000000000000LL;

int64 randomPowerWindow(int64 lo, int64 hi) {
    int64 span = hi - lo + 1;
    int64 width = min<int64>(span, rnd.next(1, 1000000));
    int64 start = rnd.next(lo, hi - width + 1);
    return rnd.next(start, start + width - 1);
}

string randomPlainNumber() {
    int length = rnd.next(1, 15);
    string value;
    value.push_back(char('1' + rnd.next(9)));
    for (int i = 1; i < length; ++i) {
        int digit;
        int style = rnd.next(4);
        if (style == 0) {
            digit = 0;
        } else if (style == 1) {
            digit = 9;
        } else {
            digit = rnd.next(10);
        }
        value.push_back(char('0' + digit));
    }
    return value;
}

int64 encryptedValue(const string& plain) {
    int length = int(plain.size());
    vector<i128> pow2(length + 1, 1), pow11(length + 1, 1);
    for (int i = 1; i <= length; ++i) {
        pow2[i] = pow2[i - 1] * 2;
        pow11[i] = pow11[i - 1] * 11;
    }

    i128 total = 0;
    for (int pos = 0; pos < length; ++pos) {
        int digit = plain[pos] - '0';
        int remaining = length - pos - 1;
        total += i128(digit) * pow2[pos] * pow11[remaining];
    }
    ensuref(1 <= total && total <= MAX_N, "constructed encrypted value is out of range");
    return int64(total);
}

int64 randomEncryptedInput() {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        string plain = randomPlainNumber();
        i128 value = 0;
        int length = int(plain.size());
        vector<i128> pow2(length + 1, 1), pow11(length + 1, 1);
        for (int i = 1; i <= length; ++i) {
            pow2[i] = pow2[i - 1] * 2;
            pow11[i] = pow11[i - 1] * 11;
        }
        for (int pos = 0; pos < length; ++pos) {
            int digit = plain[pos] - '0';
            value += i128(digit) * pow2[pos] * pow11[length - pos - 1];
        }
        if (1 <= value && value <= MAX_N) {
            return int64(value);
        }
    }
    return encryptedValue("123");
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int64 n;
    if (mode == 0) {
        vector<int64> edgeValues = {1, 2, 9, 10, 11, 42, 177, MAX_N};
        n = rnd.any(edgeValues);
    } else if (mode == 1) {
        n = rnd.next(1LL, 1000LL);
    } else if (mode == 2) {
        n = randomPowerWindow(1LL, MAX_N);
    } else if (mode <= 5) {
        n = randomEncryptedInput();
    } else if (mode == 6) {
        int digits = rnd.next(1, 18);
        int64 lo = 1;
        for (int i = 1; i < digits; ++i) lo *= 10;
        int64 hi = min(MAX_N, lo * 10 - 1);
        n = rnd.next(lo, hi);
    } else {
        n = rnd.next(MAX_N - 1000000LL, MAX_N);
    }

    println(n);
    return 0;
}
