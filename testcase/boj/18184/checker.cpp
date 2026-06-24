#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

int n, k, universeSize;

struct Claim {
    bool possible;
};

bool isGoodSet(const vector<int>& inSet) {
    vector<char> present(universeSize, 0);
    for (int value : inSet) {
        present[value] = 1;
    }

    for (int a : inSet) {
        for (int b : inSet) {
            if (!present[a | b]) {
                return false;
            }
        }
    }
    return true;
}

Claim readClaim(InStream& stream, TResult invalidVerdict) {
    string verdict = stream.readToken("[A-Za-z]+", "verdict");
    for (char& ch : verdict) {
        ch = char(toupper(ch));
    }

    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(invalidVerdict, "extra output after NO");
        }
        return {false};
    }

    if (verdict != "YES") {
        stream.quitf(invalidVerdict, "verdict must be YES or NO, found '%s'", verdict.c_str());
    }

    vector<int> values(k);
    vector<char> used(universeSize, 0);
    for (int i = 0; i < k; ++i) {
        values[i] = stream.readInt(0, universeSize - 1, format("set[%d]", i + 1).c_str());
        if (i > 0 && values[i - 1] >= values[i]) {
            stream.quitf(invalidVerdict,
                         "set elements must be strictly increasing: set[%d]=%d, set[%d]=%d",
                         i,
                         values[i - 1],
                         i + 1,
                         values[i]);
        }
        if (used[values[i]]) {
            stream.quitf(invalidVerdict, "set element %d is repeated", values[i]);
        }
        used[values[i]] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidVerdict, "extra output after set elements");
    }

    if (!isGoodSet(values)) {
        stream.quitf(invalidVerdict, "the printed set is not good");
    }

    vector<int> complement;
    complement.reserve(universeSize - k);
    for (int value = 0; value < universeSize; ++value) {
        if (!used[value]) {
            complement.push_back(value);
        }
    }
    if (!isGoodSet(complement)) {
        stream.quitf(invalidVerdict, "the complement of the printed set is not good");
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();
    universeSize = 1 << n;

    Claim jury = readClaim(ans, _fail);
    Claim participant = readClaim(ouf, _wa);

    if (jury.possible == participant.possible) {
        quitf(_ok, "%s", participant.possible ? "valid partition" : "impossible as claimed by jury");
    }
    if (!jury.possible && participant.possible) {
        quitf(_fail, "participant found a valid partition while jury says NO");
    }
    quitf(_wa, "jury provides a partition but participant says NO");
}
