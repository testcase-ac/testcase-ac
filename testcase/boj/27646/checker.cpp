#include "testlib.h"

#include <algorithm>
#include <map>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Rational {
    long long num;
    long long den;

    bool operator<(const Rational& other) const {
        return num == other.num ? den < other.den : num < other.num;
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

struct Line {
    int m;
    int b;
};

vector<int> targets;

Rational makeRational(long long num, long long den) {
    if (den < 0) {
        num = -num;
        den = -den;
    }
    long long g = gcd(abs(num), abs(den));
    return {num / g, den / g};
}

Point intersection(const Line& a, const Line& b) {
    long long den = static_cast<long long>(a.m) - b.m;
    long long xNum = static_cast<long long>(b.b) - a.b;
    long long yNum = static_cast<long long>(a.m) * b.b -
                     static_cast<long long>(b.m) * a.b;
    return {makeRational(xNum, den), makeRational(yNum, den)};
}

long long countRegions(const vector<Line>& lines) {
    map<Point, set<int>> through;

    for (int i = 0; i < static_cast<int>(lines.size()); ++i) {
        for (int j = i + 1; j < static_cast<int>(lines.size()); ++j) {
            if (lines[i].m == lines[j].m) {
                continue;
            }
            Point p = intersection(lines[i], lines[j]);
            through[p].insert(i);
            through[p].insert(j);
        }
    }

    long long regions = static_cast<long long>(lines.size()) + 1;
    for (const auto& [_, lineIds] : through) {
        regions += static_cast<long long>(lineIds.size()) - 1;
    }
    return regions;
}

void readInput() {
    int t = inf.readInt();
    targets.resize(t);
    for (int tc = 0; tc < t; ++tc) {
        targets[tc] = inf.readInt();
    }
    inf.seekEof();
}

void readAndValidateCase(InStream& stream, int tc) {
    int lineCount = stream.readInt(0, 1000, format("lineCount[%d]", tc).c_str());
    vector<Line> lines(lineCount);
    set<pair<int, int>> seen;

    for (int i = 0; i < lineCount; ++i) {
        int m = stream.readInt(-10000, 10000, format("m[%d][%d]", tc, i + 1).c_str());
        int b = stream.readInt(-10000, 10000, format("b[%d][%d]", tc, i + 1).c_str());
        if (!seen.insert({m, b}).second) {
            stream.quitf(_wa, "test case %d repeats line y=%dx+%d", tc, m, b);
        }
        lines[i] = {m, b};
    }

    long long regions = countRegions(lines);
    if (regions != targets[tc - 1]) {
        stream.quitf(_wa,
                     "test case %d creates %lld regions instead of %d",
                     tc,
                     regions,
                     targets[tc - 1]);
    }
}

void readAnswer(InStream& stream) {
    for (int tc = 1; tc <= static_cast<int>(targets.size()); ++tc) {
        readAndValidateCase(stream, tc);
    }
    stream.seekEof();
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    readInput();
    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "all %d constructions are valid", static_cast<int>(targets.size()));
}
