#include "testlib.h"

#include <string>

using namespace std;

const double EPS = 1e-6;

struct Answer {
    bool ezpz;
    double a;
    double b;
};

Answer readAnswer(InStream& stream) {
    string first = stream.readToken();
    if (first == "EZPZ") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after EZPZ");
        }
        return {true, 0.0, 0.0};
    }

    double a = stringToDouble(stream, first);
    double b = stream.readDouble();
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after numeric answer");
    }
    return {false, a, b};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.ezpz) {
        if (!participant.ezpz) {
            quitf(_wa, "expected EZPZ, found numeric answer");
        }
        quitf(_ok, "answer is EZPZ");
    }

    if (participant.ezpz) {
        quitf(_wa, "expected numeric answer, found EZPZ");
    }

    if (!doubleCompare(jury.a, participant.a, EPS)) {
        quitf(_wa, "a differs: expected %.12f, found %.12f", jury.a, participant.a);
    }
    if (!doubleCompare(jury.b, participant.b, EPS)) {
        quitf(_wa, "b differs: expected %.12f, found %.12f", jury.b, participant.b);
    }

    quitf(_ok, "answer %.12f %.12f is within tolerance", participant.a, participant.b);
}
