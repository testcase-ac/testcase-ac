#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

struct Hint {
    int type;
    int i;
    int j;
};

struct Answer {
    bool possible;
};

int n, m;
vector<Hint> hints;

void ensureEof(InStream& stream) {
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }
}

void validateWitness(InStream& stream, const string& s) {
    if ((int)s.size() != n) {
        stream.quitf(_wa, "witness length is %d, expected %d", (int)s.size(), n);
    }
    for (int pos = 0; pos < n; ++pos) {
        if (s[pos] != 'A' && s[pos] != 'B') {
            stream.quitf(_wa, "witness[%d] is '%c', expected A or B", pos + 1, s[pos]);
        }
    }

    for (int idx = 0; idx < m; ++idx) {
        int l = hints[idx].i;
        int r = hints[idx].j;
        if (hints[idx].type == 1) {
            for (int a = l, b = r; a < b; ++a, --b) {
                if (s[a] != s[b]) {
                    stream.quitf(_wa,
                                 "hint %d fails: S[%d,%d] is not a palindrome",
                                 idx + 1,
                                 l + 1,
                                 r + 1);
                }
            }
        } else {
            if (s[l] == s[r]) {
                stream.quitf(_wa,
                             "hint %d fails: S[%d] and S[%d] are both %c",
                             idx + 1,
                             l + 1,
                             r + 1,
                             s[l]);
            }
        }
    }
}

Answer readAnswer(InStream& stream) {
    string verdict = stream.readToken("[A-Za-z]+", "verdict");
    verdict = lowerCase(verdict);

    if (verdict == "no") {
        ensureEof(stream);
        return {false};
    }
    if (verdict != "yes") {
        stream.quitf(_wa, "verdict is '%s', expected Yes or No", verdict.c_str());
    }

    string witness = stream.readToken("[A-Za-z]+", "witness");
    validateWitness(stream, witness);
    ensureEof(stream);
    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    hints.reserve(m);
    for (int idx = 0; idx < m; ++idx) {
        int type = inf.readInt();
        int i = inf.readInt();
        int j = inf.readInt();
        hints.push_back({type, i - 1, j - 1});
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.possible && !participant.possible) {
        quitf(_wa, "jury has a valid witness, participant answered No");
    }
    if (!jury.possible && participant.possible) {
        quitf(_fail, "participant found a valid witness while jury answered No");
    }
    quitf(_ok, "answer is %s", participant.possible ? "Yes" : "No");
}
