#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

int n;

struct Answer {
    bool hasWitness;
};

string readVerdict(InStream& stream) {
    string token = stream.readToken("[A-Za-z]+", "verdict");
    string upper = token;
    for (char& ch : upper) {
        ch = char(toupper((unsigned char)ch));
    }
    if (upper != "YES" && upper != "NO") {
        stream.quitf(_wa, "verdict must be YES or NO, found '%s'", token.c_str());
    }
    return upper;
}

Answer readAnswer(InStream& stream) {
    string verdict = readVerdict(stream);
    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false};
    }

    vector<int> a(n);
    vector<char> used(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        a[i] = stream.readInt(1, n, format("A[%d]", i + 1).c_str());
        if (used[a[i]]) {
            stream.quitf(_wa, "value %d appears more than once", a[i]);
        }
        used[a[i]] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after sequence");
    }

    for (int i = 0; i + 2 < n; ++i) {
        int first = abs(a[i + 1] - a[i]);
        int second = abs(a[i + 2] - a[i + 1]);
        if (first != 2 * second && 2 * first != second) {
            stream.quitf(_wa,
                         "adjacent differences at positions %d,%d,%d are %d and %d",
                         i + 1,
                         i + 2,
                         i + 3,
                         first,
                         second);
        }
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(3, 2000000, "N");

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.hasWitness) {
        if (!participant.hasWitness) {
            quitf(_wa, "jury found a valid sequence but participant answered NO");
        }
        quitf(_ok, "valid sequence");
    }

    if (participant.hasWitness) {
        quitf(_fail, "participant found a valid sequence while jury answered NO");
    }
    quitf(_ok, "both answered NO");
}
