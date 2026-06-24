#include "testlib.h"

#include <map>
#include <vector>
using namespace std;

int n;
vector<int> a;
map<int, int> inputCounts;

struct Answer {
    bool impossible;
};

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, 100000, "answer[1]");

    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }

    vector<int> b(n);
    b[0] = first;
    for (int i = 1; i < n; ++i) {
        b[i] = stream.readInt(1, 100000, format("answer[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after sequence");
    }

    map<int, int> outputCounts;
    for (int i = 0; i < n; ++i) {
        if (b[i] == a[i]) {
            stream.quitf(_wa, "answer[%d]=%d is equal to input value", i + 1, b[i]);
        }
        ++outputCounts[b[i]];
    }

    if (outputCounts != inputCounts) {
        stream.quitf(_wa, "output sequence is not a permutation of the input multiset");
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 5000, "n");
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readInt(1, 100000, format("a[%d]", i + 1).c_str());
        ++inputCounts[a[i]];
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant found a valid sequence while jury claims impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant claims impossible while jury has a valid sequence");
    }

    quitf(_ok, "valid rearranged sequence");
}
