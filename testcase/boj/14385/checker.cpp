#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

struct Claim {
    int count;
};

struct TestCase {
    int n;
    int expectedCount;
};

long long valueInBase(const string& coin, int base) {
    long long value = 0;
    for (char digit : coin) {
        value = value * base + (digit - '0');
    }
    return value;
}

Claim readClaim(InStream& stream, int caseIndex, const TestCase& testCase) {
    string caseWord = stream.readToken();
    if (caseWord != "Case") {
        stream.quitf(_wa, "expected Case, found %s", caseWord.c_str());
    }
    string caseLabel = stream.readToken();
    if (caseLabel != format("#%d:", caseIndex)) {
        stream.quitf(_wa, "expected #%d:, found %s", caseIndex, caseLabel.c_str());
    }
    if (!stream.seekEoln()) {
        stream.quitf(_wa, "extra data after case header %d", caseIndex);
    }

    set<string> used;
    for (int i = 0; i < testCase.expectedCount; ++i) {
        string coin = stream.readToken();
        if ((int)coin.size() != testCase.n) {
            stream.quitf(_wa, "jamcoin[%d] has length %d instead of %d", i + 1, (int)coin.size(), testCase.n);
        }
        for (int j = 0; j < testCase.n; ++j) {
            if (coin[j] != '0' && coin[j] != '1') {
                stream.quitf(_wa, "jamcoin[%d][%d] is %c instead of 0 or 1", i + 1, j + 1, coin[j]);
            }
        }
        if (coin.front() != '1') {
            stream.quitf(_wa, "jamcoin[%d] does not start with 1", i + 1);
        }
        if (coin.back() != '1') {
            stream.quitf(_wa, "jamcoin[%d] does not end with 1", i + 1);
        }
        if (!used.insert(coin).second) {
            stream.quitf(_wa, "jamcoin[%d] duplicates %s", i + 1, coin.c_str());
        }

        for (int base = 2; base <= 10; ++base) {
            long long divisor = stream.readLong(2, 10000000000000000LL,
                                                format("divisor[%d][base=%d]", i + 1, base).c_str());
            long long value = valueInBase(coin, base);
            if (divisor >= value) {
                stream.quitf(_wa,
                             "divisor[%d][base=%d]=%lld is not nontrivial for value %lld",
                             i + 1,
                             base,
                             divisor,
                             value);
            }
            if (value % divisor != 0) {
                stream.quitf(_wa,
                             "divisor[%d][base=%d]=%lld does not divide value %lld",
                             i + 1,
                             base,
                             divisor,
                             value);
            }
        }
        if (!stream.seekEoln()) {
            stream.quitf(_wa, "extra data after jamcoin[%d]", i + 1);
        }
    }
    return {testCase.expectedCount};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int tests = inf.readInt(1, 100, "T");
    vector<TestCase> testCases(tests);
    for (int caseIndex = 1; caseIndex <= tests; ++caseIndex) {
        testCases[caseIndex - 1].n = inf.readInt(2, 64, "N");
        testCases[caseIndex - 1].expectedCount = inf.readInt(0, 100000, "J");
    }

    for (int caseIndex = 1; caseIndex <= tests; ++caseIndex) {
        Claim jury = readClaim(ans, caseIndex, testCases[caseIndex - 1]);
        Claim participant = readClaim(ouf, caseIndex, testCases[caseIndex - 1]);
        if (participant.count != jury.count) {
            quitf(_wa,
                  "participant produced %d jamcoins, jury produced %d",
                  participant.count,
                  jury.count);
        }
    }
    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }

    quitf(_ok, "all jamcoins and divisors are valid");
}
