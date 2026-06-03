#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readLine("[^]+", "hangul");
    ensuref(s.size() == 3, "hangul must be exactly one three-byte UTF-8 syllable");

    unsigned char b0 = static_cast<unsigned char>(s[0]);
    unsigned char b1 = static_cast<unsigned char>(s[1]);
    unsigned char b2 = static_cast<unsigned char>(s[2]);

    ensuref((b0 & 0xF0) == 0xE0 && (b1 & 0xC0) == 0x80 && (b2 & 0xC0) == 0x80,
            "hangul is not a valid three-byte UTF-8 sequence");

    int codepoint = ((b0 & 0x0F) << 12) | ((b1 & 0x3F) << 6) | (b2 & 0x3F);
    ensuref(0xAC00 <= codepoint && codepoint <= 0xD7A3,
            "hangul codepoint U+%04X is outside U+AC00..U+D7A3", codepoint);

    inf.readEof();
}
