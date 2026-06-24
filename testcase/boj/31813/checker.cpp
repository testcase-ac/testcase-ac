#include "testlib.h"

#include <string>

using namespace std;

struct TestCase {
    int n;
    long long k;
};

bool isRunNumber(long long x) {
    string s = to_string(x);
    for (char c : s) {
        if (c != s[0]) {
            return false;
        }
    }
    return true;
}

void readAnswer(InStream& stream, const TestCase& tc, int caseIndex) {
    int m = stream.readInt(1, tc.n + 1, format("M[%d]", caseIndex).c_str());

    long long sum = 0;
    for (int i = 0; i < m; ++i) {
        long long value = stream.readLong(1LL, tc.k, format("a[%d][%d]", caseIndex, i + 1).c_str());
        if (!isRunNumber(value)) {
            stream.quitf(_wa,
                         "case %d: summand %d is not a RUN number: %lld",
                         caseIndex,
                         i + 1,
                         value);
        }
        if (sum > tc.k - value) {
            stream.quitf(_wa,
                         "case %d: summand sum exceeds K=%lld",
                         caseIndex,
                         tc.k);
        }
        sum += value;
    }

    if (sum != tc.k) {
        stream.quitf(_wa,
                     "case %d: summand sum is %lld, expected %lld",
                     caseIndex,
                     sum,
                     tc.k);
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        TestCase tc;
        tc.n = inf.readInt();
        tc.k = inf.readLong();

        readAnswer(ans, tc, caseIndex);
        readAnswer(ouf, tc, caseIndex);
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }

    quitf(_ok, "all %d decomposition(s) are valid", t);
}
