#include "testlib.h"

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

const long long COORD_MIN = 1;
const long long COORD_MAX = 800000000LL;

struct TestCase {
    long long a;
    long long b;
    long long c;
};

struct Point {
    long long x;
    long long y;
};

struct Claim {
    bool impossible;
};

vector<TestCase> cases;

long long manhattan(const Point& lhs, const Point& rhs) {
    return llabs(lhs.x - rhs.x) + llabs(lhs.y - rhs.y);
}

long long parseTokenAsLong(InStream& stream, const string& token, long long minValue, long long maxValue, const string& name) {
    char* end = nullptr;
    errno = 0;
    long long value = strtoll(token.c_str(), &end, 10);
    if (errno == ERANGE || end == token.c_str() || *end != '\0') {
        stream.quitf(_wa, "%s is not a valid integer: %s", name.c_str(), token.c_str());
    }
    if (value < minValue || value > maxValue) {
        stream.quitf(_wa, "%s=%lld is outside [%lld, %lld]", name.c_str(), value, minValue, maxValue);
    }
    return value;
}

Point readPoint(InStream& stream, int caseIndex, int pointIndex, const string* firstToken = nullptr) {
    string xName = format("case %d x%d", caseIndex, pointIndex);
    string yName = format("case %d y%d", caseIndex, pointIndex);

    long long x;
    if (firstToken == nullptr) {
        x = stream.readLong(COORD_MIN, COORD_MAX, xName.c_str());
    } else {
        x = parseTokenAsLong(stream, *firstToken, COORD_MIN, COORD_MAX, xName);
    }
    long long y = stream.readLong(COORD_MIN, COORD_MAX, yName.c_str());
    return {x, y};
}

Claim readClaim(InStream& stream, int caseIndex) {
    string first = stream.readToken();
    if (first == "-1") {
        return {true};
    }

    Point p1 = readPoint(stream, caseIndex, 1, &first);
    Point p2 = readPoint(stream, caseIndex, 2);
    Point p3 = readPoint(stream, caseIndex, 3);

    const TestCase& tc = cases[caseIndex - 1];
    long long d12 = manhattan(p1, p2);
    long long d23 = manhattan(p2, p3);
    long long d31 = manhattan(p3, p1);
    if (d12 != tc.a) {
        stream.quitf(_wa, "case %d distance between point 1 and 2 is %lld, expected %lld", caseIndex, d12, tc.a);
    }
    if (d23 != tc.b) {
        stream.quitf(_wa, "case %d distance between point 2 and 3 is %lld, expected %lld", caseIndex, d23, tc.b);
    }
    if (d31 != tc.c) {
        stream.quitf(_wa, "case %d distance between point 3 and 1 is %lld, expected %lld", caseIndex, d31, tc.c);
    }
    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    cases.resize(t);
    for (int i = 0; i < t; ++i) {
        cases[i].a = inf.readLong(1LL, 1000000000LL, format("a[%d]", i + 1).c_str());
        cases[i].b = inf.readLong(1LL, 1000000000LL, format("b[%d]", i + 1).c_str());
        cases[i].c = inf.readLong(1LL, 1000000000LL, format("c[%d]", i + 1).c_str());
    }

    for (int i = 1; i <= t; ++i) {
        Claim jury = readClaim(ans, i);
        Claim participant = readClaim(ouf, i);

        if (jury.impossible && !participant.impossible) {
            quitf(_fail, "case %d participant provided a valid witness while jury says impossible", i);
        }
        if (!jury.impossible && participant.impossible) {
            quitf(_wa, "case %d jury provides a witness but participant says impossible", i);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }
    quitf(_ok, "all %d cases are valid", t);
}
