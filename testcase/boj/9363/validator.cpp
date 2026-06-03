#include "testlib.h"

#include <vector>

using namespace std;

namespace {

const int MAX_VALUE = 1000000;
const long long INT32_MAX_VALUE = 2147483647LL;

vector<int> buildSmallestPrimeFactor() {
    vector<int> spf(MAX_VALUE + 1);
    for (int i = 2; i <= MAX_VALUE; ++i) {
        if (spf[i] != 0) {
            continue;
        }
        spf[i] = i;
        if (1LL * i * i > MAX_VALUE) {
            continue;
        }
        for (long long j = 1LL * i * i; j <= MAX_VALUE; j += i) {
            if (spf[j] == 0) {
                spf[j] = i;
            }
        }
    }
    return spf;
}

void addFactors(int x, int sign, const vector<int>& spf, vector<int>& exponent) {
    while (x > 1) {
        int p = spf[x];
        int count = 0;
        while (x % p == 0) {
            x /= p;
            ++count;
        }
        exponent[p] += sign * count;
    }
}

bool multiplyWithinLimit(long long& value, int factor) {
    if (value > INT32_MAX_VALUE / factor) {
        return false;
    }
    value *= factor;
    return true;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<int> spf = buildSmallestPrimeFactor();

    int t = inf.readInt(1, 200, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 110000, "N");
        inf.readSpace();
        int m = inf.readInt(1, 110000, "M");
        inf.readEoln();

        vector<int> exponent(MAX_VALUE + 1);
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            int a = inf.readInt(1, MAX_VALUE, "A_i");
            addFactors(a, 1, spf, exponent);
        }
        inf.readEoln();

        for (int i = 0; i < m; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            int b = inf.readInt(1, MAX_VALUE, "B_i");
            addFactors(b, -1, spf, exponent);
        }
        inf.readEoln();

        long long numerator = 1;
        long long denominator = 1;
        for (int p = 2; p <= MAX_VALUE; ++p) {
            while (exponent[p] > 0) {
                ensuref(multiplyWithinLimit(numerator, p),
                        "reduced numerator exceeds signed 32-bit range");
                --exponent[p];
            }
            while (exponent[p] < 0) {
                ensuref(multiplyWithinLimit(denominator, p),
                        "reduced denominator exceeds signed 32-bit range");
                ++exponent[p];
            }
        }
    }

    inf.readEof();
}
