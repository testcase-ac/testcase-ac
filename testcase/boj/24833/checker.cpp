#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Claim {
    bool possible;
};

Claim readClaim(InStream& stream, int caseIndex) {
    string token = stream.readToken();
    token = lowerCase(token);

    if (token == "yes") {
        return {true};
    }
    if (token == "no") {
        return {false};
    }

    stream.quitf((&stream == &ouf) ? _wa : _fail,
                 "answer[%d] must be YES or NO, found '%s'",
                 caseIndex,
                 token.c_str());
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int q = inf.readInt(1, 500, "q");

    vector<Claim> jury(q);
    vector<Claim> participant(q);

    for (int i = 0; i < q; ++i) {
        jury[i] = readClaim(ans, i + 1);
    }
    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answers");
    }

    for (int i = 0; i < q; ++i) {
        participant[i] = readClaim(ouf, i + 1);
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answers");
    }

    for (int i = 0; i < q; ++i) {
        if (participant[i].possible != jury[i].possible) {
            quitf(_wa,
                  "answer[%d] differs: expected %s, found %s",
                  i + 1,
                  jury[i].possible ? "YES" : "NO",
                  participant[i].possible ? "YES" : "NO");
        }
    }

    quitf(_ok, "%d answers match", q);
}
