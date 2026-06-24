#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

int A, B, K;

struct Answer {
    bool impossible;
};

long long checkedLcm(long long x, long long y) {
    long long g = gcd(x, y);
    if (x / g > B / y) {
        return (long long)B + 1;
    }
    long long value = x / g * y;
    return min(value, (long long)B + 1);
}

Answer readAnswer(InStream& stream) {
    long long first = stream.readLong(-1, (long long)B + 1, "answer[1]");

    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }

    vector<long long> values(K);
    values[0] = first;
    for (int i = 1; i < K; ++i) {
        values[i] = stream.readLong(1, (long long)B + 1, format("answer[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d values", K);
    }

    set<long long> seen;
    long long gotGcd = 0;
    long long gotLcm = 1;
    for (int i = 0; i < K; ++i) {
        long long value = values[i];
        if (value <= 0) {
            stream.quitf(_wa, "answer[%d]=%lld is not positive", i + 1, value);
        }
        if (!seen.insert(value).second) {
            stream.quitf(_wa, "value %lld is repeated", value);
        }
        gotGcd = gcd(gotGcd, value);
        gotLcm = checkedLcm(gotLcm, value);
    }

    if (gotGcd != A) {
        stream.quitf(_wa, "gcd is %lld instead of %d", gotGcd, A);
    }
    if (gotLcm != B) {
        stream.quitf(_wa, "lcm is %lld instead of %d", gotLcm, B);
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    A = inf.readInt();
    B = inf.readInt();
    K = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant found a valid witness while jury output is -1");
    }

    if (participant.impossible) {
        quitf(_wa, "participant output is -1 but jury has a valid witness");
    }

    quitf(_ok, "valid witness");
}
