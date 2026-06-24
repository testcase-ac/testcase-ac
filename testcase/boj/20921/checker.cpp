#include "testlib.h"

#include <vector>
using namespace std;

int n;
long long expectedInversions;

long long countInversions(const vector<int>& values) {
    vector<int> bit(n + 1, 0);

    auto add = [&](int index) {
        for (; index <= n; index += index & -index) {
            bit[index]++;
        }
    };

    auto sum = [&](int index) {
        int result = 0;
        for (; index > 0; index -= index & -index) {
            result += bit[index];
        }
        return result;
    };

    long long inversions = 0;
    for (int i = 0; i < n; ++i) {
        inversions += i - sum(values[i]);
        add(values[i]);
    }
    return inversions;
}

long long readAnswer(InStream& stream) {
    vector<int> values(n);
    vector<int> seen(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        values[i] = stream.readInt(1, n, format("v[%d]", i + 1).c_str());
        if (seen[values[i]]) {
            stream.quitf(_wa, "value %d appears more than once", values[i]);
        }
        seen[values[i]] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after permutation");
    }

    long long inversions = countInversions(values);
    if (inversions != expectedInversions) {
        stream.quitf(_wa,
                     "expected %lld inversions, found %lld",
                     expectedInversions,
                     inversions);
    }
    return inversions;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    expectedInversions = inf.readLong();

    long long juryInversions = readAnswer(ans);
    long long participantInversions = readAnswer(ouf);

    if (participantInversions != juryInversions) {
        quitf(_fail,
              "internal checker error: jury=%lld participant=%lld",
              juryInversions,
              participantInversions);
    }

    quitf(_ok, "answer has exactly %lld inversions", participantInversions);
}
