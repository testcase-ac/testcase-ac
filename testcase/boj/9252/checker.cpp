#include "testlib.h"

#include <string>

using namespace std;

bool isSubsequence(const string& candidate, const string& source) {
    int pos = 0;
    for (char ch : source) {
        if (pos < int(candidate.size()) && candidate[pos] == ch) {
            ++pos;
        }
    }
    return pos == int(candidate.size());
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    string a = inf.readToken();
    string b = inf.readToken();

    int juryLength = ans.readInt(0, min(a.size(), b.size()), "jury LCS length");
    ans.readEoln();
    if (juryLength > 0) {
        string juryLcs = ans.readToken("[A-Z]+", "jury LCS");
        if (int(juryLcs.size()) != juryLength) {
            quitf(_fail, "jury LCS length is %d, but string has length %d",
                  juryLength, int(juryLcs.size()));
        }
        if (!isSubsequence(juryLcs, a) || !isSubsequence(juryLcs, b)) {
            quitf(_fail, "jury LCS is not a subsequence of both input strings");
        }
        ans.readEoln();
    }
    ans.readEof();

    int participantLength = ouf.readInt(0, min(a.size(), b.size()), "LCS length");
    ouf.readEoln();

    string participantLcs;
    if (participantLength > 0) {
        participantLcs = ouf.readToken("[A-Z]+", "LCS");
        if (int(participantLcs.size()) != participantLength) {
            quitf(_wa, "claimed LCS length is %d, but string has length %d",
                  participantLength, int(participantLcs.size()));
        }
        ouf.readEoln();
    }
    ouf.readEof();

    if (participantLength < juryLength) {
        quitf(_wa, "expected LCS length %d, found %d", juryLength, participantLength);
    }
    if (participantLength > juryLength) {
        quitf(_fail, "participant found longer LCS: jury=%d participant=%d",
              juryLength, participantLength);
    }
    if (!isSubsequence(participantLcs, a)) {
        quitf(_wa, "participant LCS is not a subsequence of the first input string");
    }
    if (!isSubsequence(participantLcs, b)) {
        quitf(_wa, "participant LCS is not a subsequence of the second input string");
    }

    quitf(_ok, "valid LCS of length %d", participantLength);
}
