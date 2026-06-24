#include "testlib.h"

#include <string>

using namespace std;

int n, m;
string s;

bool isVowel(char c) {
    return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

struct Claim {
    bool possible;
    string name;
};

bool isSubsequence(const string& candidate) {
    int pos = 0;
    for (char c : s) {
        if (pos < (int)candidate.size() && candidate[pos] == c) {
            ++pos;
        }
    }
    return pos == (int)candidate.size();
}

Claim readClaim(InStream& stream) {
    string decision = stream.readToken("(YES|NO)", "decision");
    stream.readEoln();

    if (decision == "NO") {
        stream.readEof();
        return {false, ""};
    }

    string candidate = stream.readToken("[A-Z]+", "T");
    stream.readEoln();
    stream.readEof();

    if ((int)candidate.size() != m) {
        stream.quitf(_wa, "T length is %d, expected %d", (int)candidate.size(), m);
    }
    if (candidate[m - 3] != 'A' || candidate[m - 2] != 'A' || isVowel(candidate[m - 1])) {
        stream.quitf(_wa, "T is not an admins' favorite name");
    }
    if (!isSubsequence(candidate)) {
        stream.quitf(_wa, "T is not a subsequence of S");
    }

    return {true, candidate};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    s = inf.readToken();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.possible) {
        if (!participant.possible) {
            quitf(_wa, "jury found a valid name but participant printed NO");
        }
        quitf(_ok, "valid name");
    }

    if (participant.possible) {
        quitf(_fail, "participant found a valid name while jury printed NO");
    }
    quitf(_ok, "both outputs report impossible");
}
