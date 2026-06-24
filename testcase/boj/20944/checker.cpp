#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int n;

string readAnswer(InStream& stream, bool jury) {
    string s = stream.readToken("[a-z]+", "answer");

    auto invalid = [&](const char* format, auto... args) {
        if (jury) {
            quitf(_fail, format, args...);
        }
        quitf(_wa, format, args...);
    };

    if ((int)s.size() != n) {
        invalid("answer length is %d, expected %d", (int)s.size(), n);
    }

    for (int i = 0; i < n / 2; ++i) {
        if (s[i] != s[n - 1 - i]) {
            invalid("answer is not a palindrome at positions %d and %d", i + 1, n - i);
        }
    }

    int half = n / 2;
    for (int i = 0; i < half; ++i) {
        if (s[i] != s[n - half + i]) {
            invalid("prefix and suffix differ at offset %d", i + 1);
        }
    }

    if (!stream.seekEof()) {
        invalid("extra output after answer");
    }

    return s;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 1000000, "N");

    readAnswer(ans, true);
    string participant = readAnswer(ouf, false);

    quitf(_ok, "valid string of length %d: %s", n, participant.c_str());
}
