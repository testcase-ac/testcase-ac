#include "testlib.h"

#include <string>

using namespace std;

int a, b, n;

bool isPrime(int x) {
    if (x < 2) {
        return false;
    }
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) {
            return false;
        }
    }
    return true;
}

struct Answer {
    bool impossible;
    string value;
};

Answer readAnswer(InStream& stream) {
    string token = stream.readToken("(-1)|([0-9]+)", "answer");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }

    if (token == "-1") {
        return {true, ""};
    }

    if ((int)token.size() != n) {
        stream.quitf(_wa, "answer length is %d, expected %d", (int)token.size(), n);
    }

    int prefix = (token[0] - '0') * 10 + (token[1] - '0');
    if (prefix != a) {
        stream.quitf(_wa, "first two digits are %d, expected %d", prefix, a);
    }

    int suffix = (token[n - 2] - '0') * 10 + (token[n - 1] - '0');
    if (suffix != b) {
        stream.quitf(_wa, "last two digits are %d, expected %d", suffix, b);
    }

    for (int i = 0; i + 1 < n; ++i) {
        int adjacent = (token[i] - '0') * 10 + (token[i + 1] - '0');
        if (!isPrime(adjacent)) {
            stream.quitf(_wa,
                         "digits %d and %d form %d, which is not prime",
                         i + 1,
                         i + 2,
                         adjacent);
        }
    }

    return {false, token};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    a = inf.readInt();
    b = inf.readInt();
    n = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "jury says impossible, but participant provides a valid witness");
    }

    if (participant.impossible) {
        quitf(_wa, "participant says impossible, but jury provides a valid witness");
    }

    quitf(_ok, "valid witness");
}
