#include "testlib.h"

#include <map>
#include <vector>

using namespace std;

int n;
vector<long long> inputA, inputB;

struct Answer {
    int matches;
};

void requireSameMultiset(InStream& stream, const vector<long long>& original,
                         const vector<long long>& supplied, const char* name) {
    map<long long, int> balance;
    for (long long value : original) {
        ++balance[value];
    }
    for (long long value : supplied) {
        --balance[value];
    }
    for (const auto& [value, count] : balance) {
        if (count != 0) {
            stream.quitf(_wa, "%s is not a permutation of the input array: value %lld has balance %d",
                         name, value, count);
        }
    }
}

Answer readAnswer(InStream& stream) {
    int claimed = stream.readInt(0, n, "claimed maximum");
    stream.readEoln();

    vector<long long> finalA(n), finalB(n);
    for (int i = 0; i < n; ++i) {
        finalA[i] = stream.readLong(1LL, 1000000000LL, format("A'[%d]", i + 1).c_str());
    }
    stream.readEoln();

    for (int i = 0; i < n; ++i) {
        finalB[i] = stream.readLong(1LL, 1000000000LL, format("B'[%d]", i + 1).c_str());
    }
    stream.readEoln();
    stream.readEof();

    requireSameMultiset(stream, inputA, finalA, "A'");
    requireSameMultiset(stream, inputB, finalB, "B'");

    int actual = 0;
    for (int i = 0; i < n; ++i) {
        if (finalA[i] == finalB[i]) {
            ++actual;
        }
    }
    if (claimed != actual) {
        stream.quitf(_wa, "claimed maximum is %d, but supplied arrays have %d matching positions",
                     claimed, actual);
    }

    return {actual};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    inputA.resize(n);
    inputB.resize(n);
    for (int i = 0; i < n; ++i) {
        inputA[i] = inf.readLong();
    }
    for (int i = 0; i < n; ++i) {
        inputB[i] = inf.readLong();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.matches < jury.matches) {
        quitf(_wa, "jury has better answer: jury=%d participant=%d",
              jury.matches, participant.matches);
    }
    if (participant.matches > jury.matches) {
        quitf(_fail, "participant found better answer: jury=%d participant=%d",
              jury.matches, participant.matches);
    }
    quitf(_ok, "answer=%d", participant.matches);
}
