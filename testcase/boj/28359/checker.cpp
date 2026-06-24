#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int n;
vector<int> inputCount;

long long sequenceValue(const vector<int>& b) {
    vector<long long> nondecreasing(n), nonincreasing(n);
    long long bestInc = 0;
    long long bestDec = 0;

    for (int i = 0; i < n; ++i) {
        nondecreasing[i] = b[i];
        nonincreasing[i] = b[i];
        for (int j = 0; j < i; ++j) {
            if (b[j] <= b[i]) {
                nondecreasing[i] = max(nondecreasing[i], nondecreasing[j] + b[i]);
            }
            if (b[j] >= b[i]) {
                nonincreasing[i] = max(nonincreasing[i], nonincreasing[j] + b[i]);
            }
        }
        bestInc = max(bestInc, nondecreasing[i]);
        bestDec = max(bestDec, nonincreasing[i]);
    }

    return bestInc + bestDec;
}

struct Answer {
    long long claimedValue;
    long long actualValue;
};

Answer readAnswer(InStream& stream) {
    long long claimedValue = stream.readLong(1LL, 2000000LL, "maximum value");

    vector<int> seen(n + 1, 0);
    vector<int> sequence(n);
    for (int i = 0; i < n; ++i) {
        sequence[i] = stream.readInt(1, n, format("B[%d]", i + 1).c_str());
        ++seen[sequence[i]];
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after sequence");
    }

    for (int value = 1; value <= n; ++value) {
        if (seen[value] != inputCount[value]) {
            stream.quitf(_wa,
                         "output sequence is not a permutation of input: value %d appears %d times, expected %d",
                         value,
                         seen[value],
                         inputCount[value]);
        }
    }

    long long actualValue = sequenceValue(sequence);
    if (claimedValue != actualValue) {
        stream.quitf(_wa,
                     "claimed value %lld does not match sequence value %lld",
                     claimedValue,
                     actualValue);
    }

    return {claimedValue, actualValue};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    inputCount.assign(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        int a = inf.readInt();
        ++inputCount[a];
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.actualValue < jury.actualValue) {
        quitf(_wa,
              "jury has better answer: jury=%lld participant=%lld",
              jury.actualValue,
              participant.actualValue);
    }
    if (participant.actualValue > jury.actualValue) {
        quitf(_fail,
              "participant found better answer: jury=%lld participant=%lld",
              jury.actualValue,
              participant.actualValue);
    }

    quitf(_ok, "answer=%lld", participant.actualValue);
}
