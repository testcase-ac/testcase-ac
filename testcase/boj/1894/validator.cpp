#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static bool isThreeDecimal(const string &s) {
    // Matches optional '-' + digits + '.' + exactly 3 digits
    // No leading '+' allowed, no leading zeros except "0.xxx"
    int n = (int)s.size();
    if (n < 5) return false; // minimal: "0.000" or "-0.000"
    int pos = 0;
    bool neg = false;
    if (s[pos] == '-') {
        neg = true;
        pos++;
        if (pos >= n) return false;
    } else if (s[pos] == '+') {
        return false; // '+' not allowed
    }

    int startDigits = pos;
    if (!isdigit(s[pos])) return false;

    // integer part
    while (pos < n && isdigit(s[pos])) pos++;
    int intLen = pos - startDigits;
    if (intLen <= 0) return false;

    // no leading zeros in integer part except "0"
    if (intLen > 1 && s[startDigits] == '0') return false;

    // must have dot and three decimals
    if (pos >= n || s[pos] != '.') return false;
    pos++;
    int decStart = pos;
    for (int i = 0; i < 3; ++i) {
        if (pos >= n || !isdigit(s[pos])) return false;
        pos++;
    }
    if (pos != n) return false; // nothing after 3 decimals

    // value range check: -10000 <= value <= 10000
    // parse as double safely
    double v = atof(s.c_str());
    if (v < -10000.0 - 1e-9 || v > 10000.0 + 1e-9) return false;

    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The problem input consists of multiple lines,
    // each with 8 real numbers: x1 y1 x2 y2 x3 y3 x4 y4
    // Each coordinate: real, mm precision (3 decimals), range [-10000, 10000].
    // Lines continue until EOF.

    int lineIndex = 0;
    while (!inf.eof()) {
        // Peek if there's data; readLine is easier/safer for variable count,
        // but we need strict whitespace handling.
        // We'll read 8 tokens per line using readToken and enforce spacing.
        // Stop if EOF is encountered before any token on a new line.
        string t[8];
        bool got = false;

        // Try to read first token of the line; if EOF here, we are done.
        if (inf.seekEof())
            break;

        // First token
        t[0] = inf.readToken("[^ \t\r\n]+", "coord0");
        got = true;
        for (int i = 1; i < 8; ++i) {
            inf.readSpace();
            t[i] = inf.readToken("[^ \t\r\n]+", ("coord" + to_string(i)).c_str());
        }
        inf.readEoln();
        lineIndex++;

        // Validate each token as canonical real with 3 decimals and in range
        for (int i = 0; i < 8; ++i) {
            ensuref(
                isThreeDecimal(t[i]),
                "Invalid coordinate format or range at line %d, index %d: '%s'",
                lineIndex, i, t[i].c_str()
            );
        }

        // Now we could additionally check that the four points define
        // two adjacent sides of some parallelogram.
        // The statement does NOT guarantee any special global property
        // like existence of answer (it always exists mathematically),
        // nor non-degeneracy, so no extra geometric checks are required.
    }

    // At this point we're at EOF
    inf.readEof();
}
