#include "testlib.h"

#include <vector>

using namespace std;

int n;
int k;
vector<int> a;

struct Answer {
    bool impossible;
    int s;
    int e;
};

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, n, "first output token");

    if (first == -1) {
        stream.readEoln();
        stream.readEof();
        return {true, -1, -1};
    }
    if (first < 1) {
        stream.quitf(_wa, "invalid start index: s=%d", first);
    }

    int second = stream.readInt(1, n, "e");
    stream.readEoln();
    stream.readEof();

    if (first > second) {
        stream.quitf(_wa, "invalid interval: s=%d is greater than e=%d", first, second);
    }

    int value = 0;
    for (int i = first; i <= second; ++i) {
        value |= a[i];
    }

    if (value != k) {
        stream.quitf(_wa,
                     "interval [%d, %d] has bitwise OR %d instead of %d",
                     first,
                     second,
                     value,
                     k);
    }

    return {false, first, second};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();
    a.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        a[i] = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail,
              "participant found valid interval [%d, %d] while jury reports impossible",
              participant.s,
              participant.e);
    }

    if (participant.impossible) {
        quitf(_wa,
              "participant reports impossible, but jury has interval [%d, %d]",
              jury.s,
              jury.e);
    }

    quitf(_ok, "valid interval [%d, %d]", participant.s, participant.e);
}
