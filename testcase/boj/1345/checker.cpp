#include "testlib.h"

#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

namespace {

constexpr double kError = 1e-9;

struct Answer {
    bool impossible;
    double value;
};

bool parseDoubleToken(const string& token, double& value) {
    errno = 0;
    char* end = nullptr;
    value = strtod(token.c_str(), &end);
    return errno != ERANGE && end == token.c_str() + token.size() && isfinite(value);
}

Answer readAnswer(InStream& stream) {
    string token = stream.readToken("[^\\s]+", "answer");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }

    double value = 0.0;
    if (!parseDoubleToken(token, value)) {
        stream.quitf(_wa, "answer is not a finite number: %s", token.c_str());
    }

    if (value == -1.0) {
        return {true, -1.0};
    }
    if (value < 0.0) {
        stream.quitf(_wa, "answer must be -1 or nonnegative, found %.17g", value);
    }
    return {false, value};
}

}  // namespace

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (!participant.impossible) {
            quitf(_wa, "jury says impossible, participant printed %.17g", participant.value);
        }
        quitf(_ok, "impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "jury answer is %.17g, participant says impossible", jury.value);
    }

    if (!doubleCompare(jury.value, participant.value, kError)) {
        quitf(_wa, "expected %.17g, found %.17g, error %.17g",
              jury.value, participant.value, doubleDelta(jury.value, participant.value));
    }

    quitf(_ok, "answer %.17g is within tolerance", participant.value);
}
