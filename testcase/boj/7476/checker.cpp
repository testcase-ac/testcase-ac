#include "testlib.h"

#include <vector>

using namespace std;

namespace {
constexpr int kMaxLength = 500;
constexpr long long kMinValue = -(1LL << 31);
constexpr long long kMaxValue = (1LL << 31) - 1;

vector<long long> firstSequence;
vector<long long> secondSequence;

struct Output {
    int length;
    vector<long long> sequence;
};

bool isSubsequence(const vector<long long>& source, const vector<long long>& candidate) {
    int pos = 0;
    for (long long value : source) {
        if (pos < static_cast<int>(candidate.size()) && candidate[pos] == value) {
            ++pos;
        }
    }
    return pos == static_cast<int>(candidate.size());
}

Output readOutput(InStream& stream) {
    int length = stream.readInt(0, kMaxLength, "length");
    stream.readEoln();

    vector<long long> sequence;
    sequence.reserve(length);
    for (int i = 0; i < length; ++i) {
        sequence.push_back(stream.readLong(kMinValue, kMaxValue, format("sequence[%d]", i + 1).c_str()));
        if (i + 1 < length) {
            stream.readSpace();
        }
    }
    stream.readEoln();
    stream.readEof();

    for (int i = 1; i < length; ++i) {
        if (sequence[i - 1] >= sequence[i]) {
            stream.quitf(_wa,
                         "sequence is not strictly increasing at positions %d and %d: %lld >= %lld",
                         i,
                         i + 1,
                         sequence[i - 1],
                         sequence[i]);
        }
    }

    if (!isSubsequence(firstSequence, sequence)) {
        stream.quitf(_wa, "sequence is not a subsequence of the first input sequence");
    }
    if (!isSubsequence(secondSequence, sequence)) {
        stream.quitf(_wa, "sequence is not a subsequence of the second input sequence");
    }

    return {length, sequence};
}

vector<long long> readInputSequence() {
    int length = inf.readInt(1, kMaxLength);
    vector<long long> sequence(length);
    for (int i = 0; i < length; ++i) {
        sequence[i] = inf.readLong(kMinValue, kMaxValue);
    }
    return sequence;
}
}  // namespace

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    firstSequence = readInputSequence();
    secondSequence = readInputSequence();

    Output jury = readOutput(ans);
    Output participant = readOutput(ouf);

    if (participant.length < jury.length) {
        quitf(_wa, "jury has longer sequence: jury=%d participant=%d", jury.length, participant.length);
    }
    if (participant.length > jury.length) {
        quitf(_fail, "participant found longer valid sequence: jury=%d participant=%d", jury.length, participant.length);
    }

    quitf(_ok, "length=%d", participant.length);
}
