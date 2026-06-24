#include "testlib.h"

#include <vector>
using namespace std;

int n;
vector<int> original;

struct Answer {
    int changes;
};

Answer readAnswer(InStream& stream) {
    int claimed = stream.readInt(0, n, "change count");
    stream.readEoln();

    int actual = 0;
    for (int i = 1; i <= n; ++i) {
        int next = stream.readInt(1, n, format("b[%d]", i).c_str());
        if (next == i) {
            stream.quitf(_wa, "b[%d] leaves phone %d not forwarded", i, i);
        }
        if (next != original[i]) {
            ++actual;
        }
    }
    stream.readEoln();
    stream.readEof();

    if (claimed != actual) {
        stream.quitf(_wa, "claimed %d changed phones, but final state changes %d", claimed, actual);
    }
    return {actual};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    original.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        original[i] = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.changes > jury.changes) {
        quitf(_wa, "jury changes %d phones, participant changes %d", jury.changes, participant.changes);
    }
    if (participant.changes < jury.changes) {
        quitf(_fail, "participant found better answer: jury=%d participant=%d", jury.changes, participant.changes);
    }
    quitf(_ok, "answer changes %d phones", participant.changes);
}
