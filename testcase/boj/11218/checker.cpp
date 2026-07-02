#include "testlib.h"

#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

const long double EPS = 1e-5L;

struct Answer {
    bool impossible;
    long double value;
};

Answer readAnswer(InStream& stream, TResult invalidVerdict) {
    string token = stream.readWord();
    if (!stream.seekEof()) {
        stream.quitf(invalidVerdict, "extra output after answer");
    }

    if (token == "impossible") {
        return {true, 0.0L};
    }

    errno = 0;
    char* end = nullptr;
    long double value = strtold(token.c_str(), &end);
    if (end == token.c_str() || *end != '\0' || errno == ERANGE || !isfinite(value)) {
        stream.quitf(invalidVerdict, "answer is neither impossible nor a finite number: %s", token.c_str());
    }

    return {false, value};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Answer jury = readAnswer(ans, _fail);
    Answer participant = readAnswer(ouf, _wa);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both answers are impossible");
        }
        quitf(_wa, "jury answer is impossible, participant printed %.12Lf", participant.value);
    }

    if (participant.impossible) {
        quitf(_wa, "jury answer is %.12Lf, participant printed impossible", jury.value);
    }

    long double error = fabsl(participant.value - jury.value);
    if (error <= EPS) {
        quitf(_ok, "answer %.12Lf is within absolute error %.12Lf", participant.value, error);
    }

    quitf(_wa, "expected %.12Lf, found %.12Lf, absolute error %.12Lf", jury.value, participant.value, error);
}
