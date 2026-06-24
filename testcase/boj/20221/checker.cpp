#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n;
vector<string> inputNumbers;

struct Claim {
    bool possible;
    vector<string> sequence;
};

int compareNumbers(const string& a, const string& b) {
    if (a.size() != b.size()) {
        return a.size() < b.size() ? -1 : 1;
    }
    if (a == b) {
        return 0;
    }
    return a < b ? -1 : 1;
}

bool canBeFlippedFrom(const string& source, const string& output) {
    if (source.size() != output.size()) {
        return false;
    }

    for (int i = 0; i < (int)source.size(); ++i) {
        if (source[i] == output[i]) {
            continue;
        }
        if ((source[i] == '6' && output[i] == '9') ||
            (source[i] == '9' && output[i] == '6')) {
            continue;
        }
        return false;
    }
    return true;
}

Claim readClaim(InStream& stream) {
    string verdict = stream.readWord("possible|impossible", "verdict");

    if (verdict == "impossible") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after impossible");
        }
        return {false, {}};
    }

    vector<string> sequence(n);
    for (int i = 0; i < n; ++i) {
        sequence[i] = stream.readWord("[1-9][0-9]*", format("sequence[%d]", i + 1).c_str());

        if (!canBeFlippedFrom(inputNumbers[i], sequence[i])) {
            stream.quitf(_wa,
                         "sequence[%d] = %s cannot be obtained from input value %s by flipping only 6 and 9",
                         i + 1,
                         sequence[i].c_str(),
                         inputNumbers[i].c_str());
        }

        if (i > 0 && compareNumbers(sequence[i - 1], sequence[i]) > 0) {
            stream.quitf(_wa,
                         "sequence is decreasing at positions %d and %d: %s > %s",
                         i,
                         i + 1,
                         sequence[i - 1].c_str(),
                         sequence[i].c_str());
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after possible sequence");
    }

    return {true, sequence};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    inputNumbers.resize(n);
    for (int i = 0; i < n; ++i) {
        inputNumbers[i] = inf.readWord();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.possible) {
        if (!participant.possible) {
            quitf(_wa, "jury provides a valid sequence, but participant reports impossible");
        }
        quitf(_ok, "valid sorted sequence");
    }

    if (participant.possible) {
        quitf(_fail, "participant found a valid sorted sequence while jury reports impossible");
    }

    quitf(_ok, "both outputs report impossible");
}
