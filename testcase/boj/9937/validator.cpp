#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Line {
    long long a;
    long long b;
    long long c;
};

struct Rational {
    __int128 num;
    __int128 den;

    bool operator<(const Rational& other) const {
        if (num != other.num) {
            return num < other.num;
        }
        return den < other.den;
    }
};

struct Point {
    Rational x;
    Rational y;

    bool operator<(const Point& other) const {
        if (x < other.x) {
            return true;
        }
        if (other.x < x) {
            return false;
        }
        return y < other.y;
    }
};

long long gcdll(long long x, long long y) {
    x = llabs(x);
    y = llabs(y);
    while (y != 0) {
        long long r = x % y;
        x = y;
        y = r;
    }
    return x;
}

Rational makeRational(__int128 num, __int128 den) {
    ensuref(den != 0, "internal error: zero rational denominator");
    if (den < 0) {
        num = -num;
        den = -den;
    }

    long long absNum = (long long)(num < 0 ? -num : num);
    long long absDen = (long long)den;
    long long g = gcdll(absNum, absDen);
    return {num / g, den / g};
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 300000, "N");
    inf.readEoln();

    vector<Line> lines;
    for (int i = 0; i < N; i++) {
        long long A = inf.readLong(-1000000000LL, 1000000000LL, "A_i");
        inf.readSpace();
        long long B = inf.readLong(-1000000000LL, 1000000000LL, "B_i");
        inf.readSpace();
        long long C = inf.readLong(-1000000000LL, 1000000000LL, "C_i");
        inf.readEoln();

        ensuref(!(A == 0 && B == 0),
                "line %d is invalid: both A and B are zero",
                i + 1);
        lines.push_back({A, B, C});
    }

    map<Point, pair<int, int>> seenIntersections;
    map<tuple<long long, long long, long long>, vector<int>> sameLines;
    map<pair<long long, long long>, vector<int>> directionGroups;

    for (int i = 0; i < N; ++i) {
        long long directionG = gcdll(lines[i].a, lines[i].b);
        long long directionA = lines[i].a / directionG;
        long long directionB = lines[i].b / directionG;
        if (directionA < 0 || (directionA == 0 && directionB < 0)) {
            directionA = -directionA;
            directionB = -directionB;
        }
        directionGroups[{directionA, directionB}].push_back(i);

        long long g = gcdll(gcdll(lines[i].a, lines[i].b), lines[i].c);
        long long a = lines[i].a / g;
        long long b = lines[i].b / g;
        long long c = lines[i].c / g;
        if (a < 0 || (a == 0 && b < 0) || (a == 0 && b == 0 && c < 0)) {
            a = -a;
            b = -b;
            c = -c;
        }

        auto key = make_tuple(a, b, c);
        sameLines[key].push_back(i);
        ensuref(sameLines[key].size() < 3,
                "lines %d, %d, and %d are identical",
                sameLines[key][0] + 1,
                sameLines[key][1] + 1,
                sameLines[key][2] + 1);
    }

    vector<vector<int>> groups;
    for (const auto& entry : directionGroups) {
        groups.push_back(entry.second);
    }

    for (int firstGroup = 0; firstGroup < (int)groups.size(); ++firstGroup) {
        for (int secondGroup = firstGroup + 1; secondGroup < (int)groups.size(); ++secondGroup) {
            for (int i : groups[firstGroup]) {
                for (int j : groups[secondGroup]) {
                    __int128 det = (__int128)lines[i].a * lines[j].b -
                                   (__int128)lines[j].a * lines[i].b;

                    Point intersection = {
                        makeRational((__int128)lines[i].b * lines[j].c -
                                         (__int128)lines[j].b * lines[i].c,
                                     det),
                        makeRational((__int128)lines[i].c * lines[j].a -
                                         (__int128)lines[j].c * lines[i].a,
                                     det),
                    };

                    auto inserted = seenIntersections.emplace(intersection, make_pair(i, j));
                    ensuref(inserted.second,
                            "lines %d, %d, and another previous pair are concurrent",
                            i + 1,
                            j + 1);
                }
            }
        }
    }

    inf.readEof();
    return 0;
}
