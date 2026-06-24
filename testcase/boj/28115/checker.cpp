#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

const long long LIMIT = 1000000000000000000LL;

int n;
vector<long long> a;

struct Claim {
    bool possible;
};

bool isArithmetic(const vector<long long>& seq) {
    if ((int)seq.size() <= 2) {
        return true;
    }
    long long diff = seq[1] - seq[0];
    for (int i = 2; i < (int)seq.size(); ++i) {
        if (seq[i] - seq[i - 1] != diff) {
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

    vector<long long> b(n), c(n);
    for (int i = 0; i < n; ++i) {
        b[i] = stream.readLong(-LIMIT, LIMIT, format("B_%d", i + 1).c_str());
    }
    for (int i = 0; i < n; ++i) {
        c[i] = stream.readLong(-LIMIT, LIMIT, format("C_%d", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after witness");
    }

    if (!isArithmetic(b)) {
        stream.quitf(_wa, "B is not an arithmetic sequence");
    }
    if (!isArithmetic(c)) {
        stream.quitf(_wa, "C is not an arithmetic sequence");
    }
    for (int i = 0; i < n; ++i) {
        if (b[i] + c[i] != a[i]) {
            stream.quitf(_wa,
                         "B_%d + C_%d = %lld, expected A_%d = %lld",
                         i + 1,
                         i + 1,
                         b[i] + c[i],
                         i + 1,
                         a[i]);
        }
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readLong();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (!jury.possible) {
        if (participant.possible) {
            quitf(_fail, "participant found a valid witness while jury answered NO");
        }
        quitf(_ok, "both answered NO");
    }

    if (!participant.possible) {
        quitf(_wa, "jury has a valid witness but participant answered NO");
    }

    quitf(_ok, "valid decomposition");
}
