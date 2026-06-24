#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int n, k;

struct Claim {
    bool possible;
};

static void validateSorted(const vector<int>& a, InStream& stream) {
    for (int i = 0; i < n; ++i) {
        if (a[i] != i + 1) {
            stream.quitf(_wa, "sequence is not sorted at position %d: found %d", i + 1, a[i]);
        }
    }
}

static Claim readClaim(InStream& stream) {
    string verdict = stream.readToken("[A-Z]+", "verdict");

    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false};
    }

    if (verdict != "YES") {
        stream.quitf(_wa, "verdict must be YES or NO, found %s", verdict.c_str());
    }

    vector<int> a(n);
    for (int i = 0; i < k; ++i) {
        a[i] = n - k + 1 + i;
    }
    for (int i = k; i < n; ++i) {
        a[i] = i - k + 1;
    }

    for (int opIndex = 1; opIndex <= 5; ++opIndex) {
        string op = stream.readToken("[a-z]+", format("operation[%d]", opIndex).c_str());
        int l = stream.readInt(1, n, format("L[%d]", opIndex).c_str());
        int r = stream.readInt(1, n, format("R[%d]", opIndex).c_str());

        if (l >= r) {
            stream.quitf(_wa, "operation %d has L >= R: %d %d", opIndex, l, r);
        }

        if (op == "swap") {
            swap(a[l - 1], a[r - 1]);
        } else if (op == "reverse") {
            reverse(a.begin() + (l - 1), a.begin() + r);
        } else {
            stream.quitf(_wa, "operation %d has invalid type %s", opIndex, op.c_str());
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after five operations");
    }
    validateSorted(a, stream);
    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.possible) {
        if (!participant.possible) {
            quitf(_wa, "participant says NO but jury provides a valid construction");
        }
        quitf(_ok, "valid construction");
    }

    if (participant.possible) {
        quitf(_fail, "participant found a valid construction while jury says NO");
    }

    quitf(_ok, "both outputs say NO");
}
