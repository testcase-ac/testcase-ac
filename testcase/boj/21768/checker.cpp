#include "testlib.h"

#include <vector>
using namespace std;

int n;
int length;
vector<long long> a;

struct Answer {
    bool impossible;
    int i;
    int j;
};

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, length - 1, "first output token");

    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, -1, -1};
    }

    int second = stream.readInt(0, length - 1, "j");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer pair");
    }

    long long lhs = a[first] + a[second];
    long long rhs = a[first & second] + a[first | second];
    if (lhs >= rhs) {
        stream.quitf(_wa,
                     "pair (%d, %d) is not valid: A[i]+A[j]=%lld, A[i&j]+A[i|j]=%lld",
                     first,
                     second,
                     lhs,
                     rhs);
    }

    return {false, first, second};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    length = 1 << n;
    a.resize(length);
    for (int i = 0; i < length; ++i) {
        a[i] = inf.readLong();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both answers report -1");
        }
        quitf(_fail,
              "participant found valid pair (%d, %d) while jury reports -1",
              participant.i,
              participant.j);
    }

    if (participant.impossible) {
        quitf(_wa,
              "participant reports -1 while jury has valid pair (%d, %d)",
              jury.i,
              jury.j);
    }

    quitf(_ok, "valid pair (%d, %d)", participant.i, participant.j);
}
