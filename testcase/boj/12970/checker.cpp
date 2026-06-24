#include "testlib.h"

#include <string>

using namespace std;

int n, k;

struct Answer {
    bool impossible;
    string s;
};

Answer readAnswer(InStream& stream) {
    string token = stream.readToken();
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }

    if (token == "-1") {
        return {true, ""};
    }

    if ((int)token.size() != n) {
        stream.quitf(_wa, "answer length is %d instead of %d", (int)token.size(), n);
    }

    int aCount = 0;
    int pairs = 0;
    for (int i = 0; i < n; ++i) {
        if (token[i] == 'A') {
            ++aCount;
        } else if (token[i] == 'B') {
            pairs += aCount;
        } else {
            stream.quitf(_wa, "answer[%d] is '%c', expected A or B", i + 1, token[i]);
        }
    }

    if (pairs != k) {
        stream.quitf(_wa, "answer has %d AB pairs instead of %d", pairs, k);
    }

    return {false, token};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both answers report impossible");
        }
        quitf(_fail, "participant found a valid answer while jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible but jury has a valid answer");
    }

    quitf(_ok, "valid answer with %d AB pairs", k);
}
