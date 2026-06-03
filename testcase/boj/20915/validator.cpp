#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

static long long bestNumberForMask(const string& cards, int mask) {
    vector<int> digits;
    for (int i = 0; i < (int)cards.size(); ++i) {
        if ((mask & (1 << i)) == 0) {
            continue;
        }

        int digit = cards[i] - '0';
        if (digit == 6) {
            digit = 9;
        }
        digits.push_back(digit);
    }

    sort(digits.rbegin(), digits.rend());

    long long value = 0;
    for (int digit : digits) {
        value = value * 10 + digit;
    }
    return value;
}

static bool hasBoundedMaximumProduct(const string& cards) {
    int n = (int)cards.size();
    int fullMask = (1 << n) - 1;

    vector<long long> best(fullMask + 1);
    for (int mask = 1; mask <= fullMask; ++mask) {
        best[mask] = bestNumberForMask(cards, mask);
    }

    constexpr long long LIMIT = 1000000000000000000LL;
    for (int mask = 1; mask < fullMask; ++mask) {
        __int128 product = (__int128)best[mask] * best[fullMask ^ mask];
        if (product > LIMIT) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        string cards = inf.readToken("[0-9]{2,18}", "cards");
        inf.readEoln();

        ensuref(hasBoundedMaximumProduct(cards),
                "maximum product exceeds 10^18 for case %d", caseIndex);
    }

    inf.readEof();
}
