#include "testlib.h"

#include <string>

using namespace std;

const int MATCHES[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

struct Answer {
    bool impossible;
};

int digitValue(char c) {
    return c - '0';
}

int twoDigitNumber(const string& token, int pos) {
    return 10 * digitValue(token[pos]) + digitValue(token[pos + 1]);
}

int twoDigitMatches(const string& token, int pos) {
    return MATCHES[digitValue(token[pos])] + MATCHES[digitValue(token[pos + 1])];
}

Answer readAnswer(InStream& stream, TResult invalidVerdict, int n) {
    string token = stream.readToken();
    if (!stream.seekEof()) {
        stream.quitf(invalidVerdict, "extra output after answer");
    }

    if (token == "impossible") {
        return {true};
    }

    if (token.size() != 8) {
        stream.quitf(invalidVerdict, "answer must be impossible or DD+DD=DD, found '%s'", token.c_str());
    }
    if (!isdigit(token[0]) || !isdigit(token[1]) || token[2] != '+' ||
        !isdigit(token[3]) || !isdigit(token[4]) || token[5] != '=' ||
        !isdigit(token[6]) || !isdigit(token[7])) {
        stream.quitf(invalidVerdict, "answer must have format DD+DD=DD, found '%s'", token.c_str());
    }

    int a = twoDigitNumber(token, 0);
    int b = twoDigitNumber(token, 3);
    int c = twoDigitNumber(token, 6);
    if (a + b != c) {
        stream.quitf(invalidVerdict, "equation is invalid: %02d+%02d!=%02d", a, b, c);
    }

    int used = twoDigitMatches(token, 0) + twoDigitMatches(token, 3) + twoDigitMatches(token, 6) + 4;
    if (used != n) {
        stream.quitf(invalidVerdict, "equation uses %d matches instead of %d", used, n);
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();

    Answer jury = readAnswer(ans, _fail, n);
    Answer participant = readAnswer(ouf, _wa, n);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs are impossible");
        }
        quitf(_fail, "participant found a valid equation while jury says impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "jury has a valid equation but participant says impossible");
    }

    quitf(_ok, "valid equation");
}
