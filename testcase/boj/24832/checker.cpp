#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

int n, m;
set<string> available;

struct Answer {
    int length;
};

static void invalid(InStream& stream, bool jury, const char* message) {
    stream.quitf(jury ? _fail : _wa, "%s", message);
}

static Answer readAnswer(InStream& stream, bool jury) {
    int claimedLength = stream.readInt(0, n * m, "palindrome length");
    stream.readEoln();

    string palindrome;
    if (claimedLength == 0) {
        if (!stream.seekEof()) {
            palindrome = stream.readLine();
            if (!palindrome.empty()) {
                invalid(stream, jury, "non-empty palindrome line for length 0");
            }
        }
        stream.readEof();
        return {0};
    }

    palindrome = stream.readToken("[a-z]+", "palindrome");
    stream.readEoln();
    stream.readEof();

    if ((int)palindrome.size() != claimedLength) {
        stream.quitf(jury ? _fail : _wa,
                     "claimed length is %d but palindrome length is %d",
                     claimedLength, (int)palindrome.size());
    }
    if (claimedLength % m != 0) {
        stream.quitf(jury ? _fail : _wa,
                     "palindrome length %d is not divisible by m=%d",
                     claimedLength, m);
    }

    string reversed = palindrome;
    reverse(reversed.begin(), reversed.end());
    if (palindrome != reversed) {
        invalid(stream, jury, "output string is not a palindrome");
    }

    set<string> used;
    for (int pos = 0; pos < claimedLength; pos += m) {
        string part = palindrome.substr(pos, m);
        if (!available.count(part)) {
            stream.quitf(jury ? _fail : _wa,
                         "block '%s' is not one of the input strings",
                         part.c_str());
        }
        if (!used.insert(part).second) {
            stream.quitf(jury ? _fail : _wa,
                         "input string '%s' is used more than once",
                         part.c_str());
        }
    }

    return {claimedLength};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    for (int i = 0; i < n; ++i) {
        available.insert(inf.readToken());
    }

    Answer jury = readAnswer(ans, true);
    Answer participant = readAnswer(ouf, false);

    if (participant.length < jury.length) {
        quitf(_wa, "participant length %d is less than jury length %d",
              participant.length, jury.length);
    }
    if (participant.length > jury.length) {
        quitf(_fail,
              "participant found a longer valid palindrome: participant=%d jury=%d",
              participant.length, jury.length);
    }

    quitf(_ok, "accepted palindrome length %d", participant.length);
}
