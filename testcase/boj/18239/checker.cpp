#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <sstream>
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
    stream.readEoln();

    vector<int> a(n);
    for (int i = 0; i < k; ++i) {
        a[i] = n - k + 1 + i;
    }
    for (int i = k; i < n; ++i) {
        a[i] = i - k + 1;
    }

    for (int opIndex = 1; opIndex <= 5; ++opIndex) {
        string line = stream.readLine("[^]*", format("operation[%d]", opIndex).c_str());
        string normalized;
        for (size_t i = 0; i < line.size(); ++i) {
            unsigned char ch = static_cast<unsigned char>(line[i]);
            if (ch == 0xC2 && i + 1 < line.size() && static_cast<unsigned char>(line[i + 1]) == 0xA0) {
                normalized.push_back(' ');
                ++i;
            } else {
                normalized.push_back(line[i]);
            }
        }

        string op, extra;
        int l, r;
        stringstream ss(normalized);
        if (!(ss >> op >> l >> r) || (ss >> extra)) {
            stream.quitf(_wa, "operation %d must have form '<swap|reverse> L R'", opIndex);
        }

        if (l < 1 || l > n || r < 1 || r > n) {
            stream.quitf(_wa, "operation %d indices out of range: %d %d", opIndex, l, r);
        }
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
