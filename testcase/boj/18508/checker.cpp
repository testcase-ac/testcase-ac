#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

const long long SCALE = 10000;

struct Point {
    long long x;
    long long y;
};

struct Answer {
    bool possible;
};

int n;
vector<Point> points;

long long parseScaled(InStream& stream, const string& name) {
    string s = stream.readToken();
    if (s.empty()) {
        stream.quitf(_wa, "%s is empty", name.c_str());
    }

    int pos = 0;
    bool neg = false;
    if (s[pos] == '-') {
        neg = true;
        ++pos;
        if (pos == (int)s.size()) {
            stream.quitf(_wa, "%s has no integer part", name.c_str());
        }
    }

    __int128 integer = 0;
    int integerDigits = 0;
    while (pos < (int)s.size() && isdigit((unsigned char)s[pos])) {
        integer = integer * 10 + (s[pos] - '0');
        ++integerDigits;
        ++pos;
        if (integer > (__int128)4'000'000'000'000'000LL) {
            stream.quitf(_wa, "%s is too large", name.c_str());
        }
    }
    if (integerDigits == 0) {
        stream.quitf(_wa, "%s has no integer part", name.c_str());
    }

    long long frac = 0;
    int fracDigits = 0;
    if (pos < (int)s.size() && s[pos] == '.') {
        ++pos;
        while (pos < (int)s.size()) {
            if (!isdigit((unsigned char)s[pos])) {
                stream.quitf(_wa, "%s has an invalid decimal digit", name.c_str());
            }
            if (fracDigits == 4) {
                stream.quitf(_wa, "%s has more than four digits after the decimal point", name.c_str());
            }
            frac = frac * 10 + (s[pos] - '0');
            ++fracDigits;
            ++pos;
        }
        while (fracDigits < 4) {
            frac *= 10;
            ++fracDigits;
        }
    } else if (pos != (int)s.size()) {
        stream.quitf(_wa, "%s has an invalid character", name.c_str());
    }

    __int128 value = integer * SCALE + frac;
    if (neg) {
        value = -value;
    }
    if (value < LLONG_MIN || value > LLONG_MAX) {
        stream.quitf(_wa, "%s is outside supported range", name.c_str());
    }
    return (long long)value;
}

Answer readAnswer(InStream& stream) {
    string verdict = stream.readToken("[A-Za-z]+", "verdict");
    for (char& c : verdict) {
        c = (char)tolower((unsigned char)c);
    }

    if (verdict == "no") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after No");
        }
        return {false};
    }
    if (verdict != "yes") {
        stream.quitf(_wa, "expected Yes or No, found '%s'", verdict.c_str());
    }

    vector<char> deleted(n, 0);
    int deletedCount = 0;

    for (int step = 0; step < n / 2; ++step) {
        long long x1 = parseScaled(stream, format("x1[%d]", step + 1));
        long long y1 = parseScaled(stream, format("y1[%d]", step + 1));
        long long x2 = parseScaled(stream, format("x2[%d]", step + 1));
        long long y2 = parseScaled(stream, format("y2[%d]", step + 1));

        long long width = llabs(x1 - x2);
        long long height = llabs(y1 - y2);
        if (width == 0 || width != height) {
            stream.quitf(_wa, "figure %d is not a non-degenerate square", step + 1);
        }

        long long minX = min(x1, x2);
        long long maxX = max(x1, x2);
        long long minY = min(y1, y2);
        long long maxY = max(y1, y2);

        vector<int> inside;
        for (int i = 0; i < n; ++i) {
            if (deleted[i]) {
                continue;
            }
            long long px = points[i].x * SCALE;
            long long py = points[i].y * SCALE;
            if (minX <= px && px <= maxX && minY <= py && py <= maxY) {
                inside.push_back(i);
            }
        }

        if ((int)inside.size() != 2) {
            stream.quitf(_wa, "square %d contains %d remaining points instead of 2", step + 1, (int)inside.size());
        }
        for (int idx : inside) {
            deleted[idx] = 1;
        }
        deletedCount += 2;
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after deletion sequence");
    }
    if (deletedCount != n) {
        stream.quitf(_wa, "deleted %d points instead of %d", deletedCount, n);
    }
    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 3000, "n");
    points.resize(n);
    for (int i = 0; i < n; ++i) {
        points[i].x = inf.readLong(0, 1000000000LL, format("x[%d]", i + 1).c_str());
        points[i].y = inf.readLong(0, 1000000000LL, format("y[%d]", i + 1).c_str());
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (!jury.possible && participant.possible) {
        quitf(_fail, "participant found a valid deletion sequence while jury says No");
    }
    if (jury.possible && !participant.possible) {
        quitf(_wa, "jury has a deletion sequence but participant says No");
    }
    quitf(_ok, "valid %s answer", participant.possible ? "Yes" : "No");
}
