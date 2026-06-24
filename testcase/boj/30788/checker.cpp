#include "testlib.h"

#include <cctype>
#include <string>
#include <vector>

using namespace std;

int n;
vector<int> angle;

string upperToken(string s) {
    for (char& c : s) {
        c = char(toupper((unsigned char)c));
    }
    return s;
}

struct Claim {
    bool possible;
};

void streamQuit(InStream& stream, TResult result, const char* format, ...) {
    FMT_TO_RESULT(format, format, message);
    stream.quit(result, message.c_str());
}

Claim readClaim(InStream& stream, TResult invalidResult) {
    string verdict = upperToken(stream.readToken("[A-Za-z]+", "verdict"));
    if (verdict == "NO") {
        if (!stream.seekEof()) {
            streamQuit(stream, invalidResult, "extra output after NO");
        }
        return {false};
    }
    if (verdict != "YES") {
        streamQuit(stream, invalidResult, "verdict must be YES or NO, found %s", verdict.c_str());
    }

    vector<int> seen(n + 1, 0);
    int alternatingSum = 0;
    for (int i = 1; i <= n; ++i) {
        int idx = stream.readInt(1, n, format("order[%d]", i).c_str());
        if (seen[idx]) {
            streamQuit(stream, invalidResult, "axis %d is used more than once", idx);
        }
        seen[idx] = 1;

        if (i % 2 == 0) {
            alternatingSum += angle[idx];
        } else {
            alternatingSum -= angle[idx];
        }
        alternatingSum %= 180;
        if (alternatingSum < 0) {
            alternatingSum += 180;
        }
    }
    if (!stream.seekEof()) {
        streamQuit(stream, invalidResult, "extra output after reflection order");
    }

    if (n % 2 != 0) {
        streamQuit(stream, invalidResult, "YES witness has odd number of reflections");
    }
    if (alternatingSum != 0) {
        streamQuit(stream, invalidResult,
                   "reflection order produces rotation offset %d modulo 180", alternatingSum);
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 500, "N");
    angle.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        angle[i] = inf.readInt(0, 179, format("A[%d]", i).c_str());
    }

    Claim jury = readClaim(ans, _fail);
    Claim participant = readClaim(ouf, _wa);

    if (jury.possible != participant.possible) {
        if (participant.possible) {
            quitf(_fail, "participant provided a valid witness while jury says NO");
        }
        quitf(_wa, "jury says YES but participant says NO");
    }

    if (!jury.possible) {
        quitf(_ok, "both outputs report NO");
    }
    quitf(_ok, "valid reflection order");
}
