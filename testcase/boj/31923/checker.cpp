#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n, p, q;
vector<int> a, b;

struct Answer {
    bool possible;
    vector<int> operations;
};

Answer readAnswer(InStream& stream) {
    string verdict = stream.readWord();
    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false, {}};
    }
    if (verdict != "YES") {
        stream.quitf(_wa, "verdict must be YES or NO, found '%s'", verdict.c_str());
    }

    vector<int> operations(n);
    for (int i = 0; i < n; ++i) {
        operations[i] = stream.readInt(0, 10000, format("operations[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after YES witness");
    }

    for (int i = 0; i < n; ++i) {
        long long strawberries = a[i] + 1LL * operations[i] * p;
        long long grapes = b[i] + 1LL * operations[i] * q;
        if (strawberries != grapes) {
            stream.quitf(_wa,
                         "skewer %d is not balanced: A_i + x_i*P = %lld, B_i + x_i*Q = %lld",
                         i + 1,
                         strawberries,
                         grapes);
        }
    }

    return {true, operations};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    p = inf.readInt();
    q = inf.readInt();

    a.resize(n);
    b.resize(n);
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readInt();
    }
    for (int i = 0; i < n; ++i) {
        b[i] = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.possible) {
        if (!participant.possible) {
            quitf(_wa, "jury has a valid YES witness, participant answered NO");
        }
        quitf(_ok, "valid YES witness");
    }

    if (participant.possible) {
        quitf(_fail, "participant found a valid YES witness while jury answered NO");
    }

    quitf(_ok, "both answered NO");
}
