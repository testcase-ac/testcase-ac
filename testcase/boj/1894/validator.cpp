#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x;
    long long y;
};

static long long readMillimeterCoordinate(const string& token, int line, int index) {
    int pos = 0;
    bool negative = false;
    if (pos < (int)token.size() && token[pos] == '-') {
        negative = true;
        ++pos;
    }

    ensuref(pos < (int)token.size() && isdigit((unsigned char)token[pos]),
            "line %d coordinate %d has invalid numeric format: %s", line, index, token.c_str());

    int firstDigit = pos;
    while (pos < (int)token.size() && isdigit((unsigned char)token[pos])) {
        ++pos;
    }
    int integerDigits = pos - firstDigit;
    ensuref(integerDigits == 1 || token[firstDigit] != '0',
            "line %d coordinate %d has leading zeroes: %s", line, index, token.c_str());

    ensuref(pos < (int)token.size() && token[pos] == '.',
            "line %d coordinate %d is missing decimal point: %s", line, index, token.c_str());
    ++pos;

    ensuref(pos + 3 == (int)token.size(),
            "line %d coordinate %d must have exactly three decimal digits: %s",
            line, index, token.c_str());

    long long whole = 0;
    for (int i = firstDigit; i < firstDigit + integerDigits; ++i) {
        whole = whole * 10 + (token[i] - '0');
    }

    long long frac = 0;
    for (int i = 0; i < 3; ++i) {
        ensuref(isdigit((unsigned char)token[pos + i]),
                "line %d coordinate %d has invalid decimal digit: %s", line, index, token.c_str());
        frac = frac * 10 + (token[pos + i] - '0');
    }

    long long value = whole * 1000 + frac;
    if (negative) {
        value = -value;
    }
    ensuref(-10000000 <= value && value <= 10000000,
            "line %d coordinate %d is outside [-10000.000, 10000.000]: %s",
            line, index, token.c_str());
    return value;
}

static bool samePoint(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}

static long long cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int lines = 0;
    while (!inf.seekEof()) {
        ensuref(lines < 100000, "too many input lines");
        ++lines;

        string token[8];
        for (int i = 0; i < 8; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            token[i] = inf.readToken("[^ \t\r\n]+", ("coordinate_" + to_string(i + 1)).c_str());
        }
        inf.readEoln();

        Point p[4];
        for (int i = 0; i < 4; ++i) {
            p[i].x = readMillimeterCoordinate(token[2 * i], lines, 2 * i + 1);
            p[i].y = readMillimeterCoordinate(token[2 * i + 1], lines, 2 * i + 2);
        }

        ensuref(!samePoint(p[0], p[1]), "line %d first side has zero length", lines);
        ensuref(!samePoint(p[2], p[3]), "line %d second side has zero length", lines);

        int sharedFirst = -1;
        int sharedSecond = -1;
        int sharedCount = 0;
        for (int i = 0; i < 2; ++i) {
            for (int j = 2; j < 4; ++j) {
                if (samePoint(p[i], p[j])) {
                    sharedFirst = i;
                    sharedSecond = j;
                    ++sharedCount;
                }
            }
        }

        ensuref(sharedCount == 1, "line %d sides must share exactly one endpoint", lines);
        Point shared = p[sharedFirst];
        Point otherFirst = p[1 - sharedFirst];
        Point otherSecond = p[5 - sharedSecond];
        ensuref(cross(shared, otherFirst, otherSecond) != 0,
                "line %d adjacent sides must not be collinear", lines);
    }

    ensuref(lines > 0, "input must contain at least one line");
    inf.readEof();
}
