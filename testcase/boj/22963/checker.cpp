#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

const long long MIN_X = 1;
const long long MAX_X = 1000000000LL;

int n;
vector<long long> original;

struct Claim {
    bool possible;
};

bool isSorted(const vector<long long>& a) {
    for (int i = 1; i < (int)a.size(); ++i) {
        if (a[i - 1] > a[i]) {
            return false;
        }
    }
    return true;
}

Claim readClaim(InStream& stream) {
    string verdict = stream.readToken("YES|NO", "verdict");
    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false};
    }

    int k = stream.readInt(0, 3, "K");
    vector<long long> a = original;
    for (int op = 0; op < k; ++op) {
        int index = stream.readInt(1, n, format("operation[%d].i", op + 1).c_str());
        long long value = stream.readLong(MIN_X, MAX_X, format("operation[%d].X", op + 1).c_str());
        a[index - 1] = value;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after YES witness");
    }

    if (!isSorted(a)) {
        stream.quitf(_wa, "YES claim does not make the sequence sorted");
    }
    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    original = inf.readLongs(n);

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.possible) {
        if (!participant.possible) {
            quitf(_wa, "jury has a valid YES witness, but participant printed NO");
        }
        quitf(_ok, "valid YES witness");
    }

    if (!participant.possible) {
        quitf(_ok, "both jury and participant printed NO");
    }
    quitf(_fail, "participant found a valid YES witness while jury printed NO");
}
