#include "testlib.h"

#include <string>

using namespace std;

struct Claim {
    bool hasSolution;
    string value;
};

int n;
int d;

bool isAllDigits(const string& s) {
    for (char c : s) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

int modulo(const string& s, int mod) {
    int value = 0;
    for (char c : s) {
        value = (static_cast<long long>(value) * 10 + (c - '0')) % mod;
    }
    return value;
}

Claim readClaim(InStream& stream) {
    string first = stream.readToken();

    if (first == "No") {
        string second = stream.readToken();
        if (second != "solution") {
            stream.quitf(_wa, "expected 'No solution', found 'No %s'", second.c_str());
        }
        stream.readEoln();
        stream.readEof();
        return {false, ""};
    }

    if (!isAllDigits(first)) {
        stream.quitf(_wa, "answer must be a decimal integer or 'No solution'");
    }
    if (static_cast<int>(first.size()) != n) {
        stream.quitf(_wa, "answer has %d digits, expected %d", static_cast<int>(first.size()), n);
    }
    if (first[0] == '0') {
        stream.quitf(_wa, "answer has a leading zero");
    }
    if (modulo(first, d) != 0) {
        stream.quitf(_wa, "answer is not divisible by %d", d);
    }

    stream.readEoln();
    stream.readEof();
    return {true, first};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    d = inf.readInt();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (!jury.hasSolution) {
        if (participant.hasSolution) {
            quitf(_fail, "participant found a valid %d-digit multiple of %d while jury says no solution", n, d);
        }
        quitf(_ok, "both outputs report no solution");
    }

    if (!participant.hasSolution) {
        quitf(_wa, "jury provides a valid solution but participant reports no solution");
    }

    quitf(_ok, "valid %d-digit multiple of %d", n, d);
}
