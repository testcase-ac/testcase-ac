#include "testlib.h"

#include <vector>

using namespace std;

int n, k, x;

struct Answer {
    bool impossible;
};

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, 999999, "answer[1]");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }

    vector<int> a(n);
    a[0] = first;
    if (a[0] <= 0) {
        stream.quitf(_wa, "answer[1]=%d is not positive", a[0]);
    }

    for (int i = 1; i < n; ++i) {
        a[i] = stream.readInt(1, 999999, format("answer[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after array");
    }

    long long pairs = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (abs(a[i] - a[j]) >= x) {
                ++pairs;
            }
        }
    }

    if (pairs != k) {
        stream.quitf(_wa, "found %lld qualifying pairs, expected %d", pairs, k);
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();
    x = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant found a valid array while jury claims impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant claims impossible but jury provides a valid array");
    }

    quitf(_ok, "valid array");
}
