#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Answer {
    long long score;
};

int n;
vector<int> inputValues;

Answer readAnswer(InStream& stream) {
    vector<int> outputValues(n);
    for (int i = 0; i < n; ++i) {
        outputValues[i] = stream.readInt(-1000000, 1000000, format("a[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after permutation");
    }

    vector<int> sortedOutput = outputValues;
    sort(sortedOutput.begin(), sortedOutput.end());
    if (sortedOutput != inputValues) {
        stream.quitf(_wa, "output is not a permutation of the input sequence");
    }

    long long score = 0;
    for (int i = 0; i + 1 < n; ++i) {
        score += 1LL * outputValues[i] * outputValues[i + 1];
    }
    return {score};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    inputValues.resize(n);
    for (int i = 0; i < n; ++i) {
        inputValues[i] = inf.readInt();
    }
    sort(inputValues.begin(), inputValues.end());

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.score < jury.score) {
        quitf(_wa, "participant score %lld is less than jury score %lld",
              participant.score, jury.score);
    }
    if (participant.score > jury.score) {
        quitf(_fail, "participant score %lld is greater than jury score %lld",
              participant.score, jury.score);
    }

    quitf(_ok, "score %lld", participant.score);
}
