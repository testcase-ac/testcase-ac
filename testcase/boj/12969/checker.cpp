#include "testlib.h"

#include <string>

using namespace std;

int n, k;

struct Answer {
    bool impossible;
    string s;
};

long long countIncreasingPairs(const string& s) {
    long long pairs = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        for (int j = i + 1; j < (int)s.size(); ++j) {
            if (s[i] < s[j]) {
                ++pairs;
            }
        }
    }
    return pairs;
}

Answer readAnswer(InStream& stream) {
    string token = stream.readToken("-1|[ABC]{1,30}", "answer");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }

    if (token == "-1") {
        return {true, ""};
    }

    if ((int)token.size() != n) {
        stream.quitf(_wa, "answer length is %d, expected %d", (int)token.size(), n);
    }

    long long pairs = countIncreasingPairs(token);
    if (pairs != k) {
        stream.quitf(_wa, "answer has %lld increasing pairs, expected %d", pairs, k);
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
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found valid answer while jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible, but jury has a valid answer");
    }

    quitf(_ok, "valid answer with %d increasing pairs", k);
}
