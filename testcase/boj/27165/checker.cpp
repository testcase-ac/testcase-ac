#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

int n;
int x;
vector<int> a;

struct Answer {
    bool possible;
    int from = -1;
    int to = -1;
};

[[noreturn]] void invalid(InStream& stream, bool jury, const char* message) {
    stream.quitf(jury ? _fail : _wa, "%s", message);
}

Answer readAnswer(InStream& stream, bool jury) {
    string verdict = stream.readToken("[A-Z]+", "verdict");

    if (verdict == "NO") {
        if (!stream.seekEof()) {
            invalid(stream, jury, "extra output after NO");
        }
        return {false, -1, -1};
    }

    if (verdict != "YES") {
        invalid(stream, jury, "verdict must be YES or NO");
    }

    int from = stream.readInt(0, n, "from");
    int to = stream.readInt(0, n, "to");
    if (!stream.seekEof()) {
        invalid(stream, jury, "extra output after move");
    }

    if (from + x != to) {
        stream.quitf(jury ? _fail : _wa,
                     "move must advance by x=%d, found %d -> %d", x, from, to);
    }
    if (a[from] == 0) {
        stream.quitf(jury ? _fail : _wa, "there is no piece at start cell %d", from);
    }

    vector<int> after = a;
    --after[from];
    ++after[to];
    for (int i = 0; i <= n; ++i) {
        if (after[i] == 1) {
            stream.quitf(jury ? _fail : _wa,
                         "cell %d has exactly one piece after move %d -> %d",
                         i, from, to);
        }
    }

    return {true, from, to};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    a = inf.readInts(n + 1);
    x = inf.readInt();

    Answer jury = readAnswer(ans, true);
    Answer participant = readAnswer(ouf, false);

    if (!jury.possible) {
        if (!participant.possible) {
            quitf(_ok, "both outputs report NO");
        }
        quitf(_fail, "participant found valid move %d -> %d while jury reports NO",
              participant.from, participant.to);
    }

    if (!participant.possible) {
        quitf(_wa, "jury has valid move %d -> %d, participant reports NO",
              jury.from, jury.to);
    }

    quitf(_ok, "valid move %d -> %d", participant.from, participant.to);
}
