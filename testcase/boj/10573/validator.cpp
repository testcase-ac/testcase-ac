#include "testlib.h"
#include <limits>
#include <string>
#include <vector>
using namespace std;

const __int128 LIMIT = (__int128)numeric_limits<long long>::max();
const __int128 OVER_LIMIT = LIMIT + 1;

__int128 addCapped(__int128 a, __int128 b) {
    if (a > OVER_LIMIT - b) return OVER_LIMIT;
    return a + b;
}

bool outputFits64Bit(const string& s) {
    for (int i = 1; i < (int)s.size(); ++i) {
        if (s[i - 1] > s[i]) return true;
    }

    int n = (int)s.size();
    vector<vector<__int128>> memo(10, vector<__int128>(n + 1, -1));

    auto countFrom = [&](auto&& self, int digit, int pos) -> __int128 {
        if (pos == n) return 1;
        __int128& ret = memo[digit][pos];
        if (ret != -1) return ret;

        ret = 0;
        for (int next = digit; next <= 9; ++next) {
            ret = addCapped(ret, self(self, next, pos + 1));
        }
        return ret;
    };

    __int128 countLess = 0;
    int minDigit = 0;
    for (int pos = 0; pos < n; ++pos) {
        int current = s[pos] - '0';
        for (int digit = minDigit; digit < current; ++digit) {
            countLess = addCapped(countLess, countFrom(countFrom, digit, pos + 1));
        }
        minDigit = current;
    }

    ensuref(countLess <= LIMIT, "64-bit output guarantee exceeded for n=%s", s.c_str());
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: the statement does not bound the number of test cases; use the local default cap.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        string n = inf.readToken("[1-9][0-9]{0,79}", "n");
        inf.readEoln();

        outputFits64Bit(n);
    }

    inf.readEof();
    return 0;
}
