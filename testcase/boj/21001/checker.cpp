#include "testlib.h"

#include <string>
using namespace std;

struct TestCase {
    int n;
    char required;
    string lower;
    string upper;
};

struct Claim {
    bool impossible;
    string word;
};

Claim readClaim(InStream& stream, const TestCase& tc, int index, TResult invalidVerdict) {
    string token = stream.readToken("[a-z]+|NO", format("answer[%d]", index).c_str());
    if (token == "NO") {
        return {true, ""};
    }

    if ((int)token.size() != tc.n) {
        stream.quitf(invalidVerdict,
                     "answer[%d] has length %d instead of %d",
                     index,
                     (int)token.size(),
                     tc.n);
    }
    if (!(tc.lower < token && token < tc.upper)) {
        stream.quitf(invalidVerdict,
                     "answer[%d] is not strictly between s and t",
                     index);
    }
    if (token.find(tc.required) == string::npos) {
        stream.quitf(invalidVerdict,
                     "answer[%d] does not contain required character '%c'",
                     index,
                     tc.required);
    }

    return {false, token};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int z = inf.readInt();
    for (int i = 1; i <= z; ++i) {
        TestCase tc;
        string required;
        tc.n = inf.readInt();
        required = inf.readToken();
        tc.required = required[0];
        tc.lower = inf.readToken();
        tc.upper = inf.readToken();

        Claim jury = readClaim(ans, tc, i, _fail);
        Claim participant = readClaim(ouf, tc, i, _wa);

        if (jury.impossible) {
            if (!participant.impossible) {
                quitf(_fail,
                      "participant found valid answer[%d] while jury says NO: %s",
                      i,
                      participant.word.c_str());
            }
        } else if (participant.impossible) {
            quitf(_wa,
                  "participant says NO for answer[%d], but jury provides a valid word",
                  i);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answers");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answers");
    }

    quitf(_ok, "all answers are valid");
}
