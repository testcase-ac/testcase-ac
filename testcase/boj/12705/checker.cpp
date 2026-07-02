#include "testlib.h"

#include <cstdlib>
#include <cerrno>
#include <climits>
#include <string>
#include <vector>

using namespace std;

struct TestCase {
    int n;
    int m;
    long long area2;
};

struct Point {
    long long x;
    long long y;
};

struct Claim {
    bool impossible;
};

static vector<TestCase> tests;

static long long doubledArea(const vector<Point>& p) {
    long long value = p[0].x * (p[1].y - p[2].y) +
                      p[1].x * (p[2].y - p[0].y) +
                      p[2].x * (p[0].y - p[1].y);
    return llabs(value);
}

static long long parseBoundedInteger(InStream& stream,
                                     const string& token,
                                     long long low,
                                     long long high,
                                     const string& name) {
    char* end = nullptr;
    errno = 0;
    long long value = strtoll(token.c_str(), &end, 10);
    if (errno == ERANGE || end == token.c_str() || *end != '\0') {
        stream.quitf(_wa, "%s is not an integer: %s", name.c_str(), token.c_str());
    }
    if (value < low || value > high) {
        stream.quitf(_wa,
                     "%s is %lld, expected between %lld and %lld",
                     name.c_str(),
                     value,
                     low,
                     high);
    }
    return value;
}

static Claim readCaseClaim(InStream& stream, int caseNo) {
    string label = stream.readToken();
    if (label != "Case") {
        stream.quitf(_wa, "case %d label is %s, expected Case", caseNo, label.c_str());
    }
    string number = stream.readToken();
    string expectedNumber = format("#%d:", caseNo);
    if (number != expectedNumber) {
        stream.quitf(_wa, "case %d number is %s, expected %s", caseNo, number.c_str(), expectedNumber.c_str());
    }

    string firstToken = stream.readToken();
    if (firstToken == "IMPOSSIBLE") {
        return {true};
    }

    const TestCase& tc = tests[caseNo - 1];
    vector<Point> p(3);
    p[0].x = parseBoundedInteger(stream, firstToken, 0, tc.n, format("x_1 in case %d", caseNo));
    p[0].y = stream.readLong(0LL, (long long)tc.m, format("y_%d in case %d", 1, caseNo).c_str());
    for (int i = 1; i < 3; ++i) {
        p[i].x = stream.readLong(0LL, (long long)tc.n, format("x_%d in case %d", i + 1, caseNo).c_str());
        p[i].y = stream.readLong(0LL, (long long)tc.m, format("y_%d in case %d", i + 1, caseNo).c_str());
    }

    long long got = doubledArea(p);
    if (got != tc.area2) {
        stream.quitf(_wa,
                     "case %d has doubled area %lld, expected %lld",
                     caseNo,
                     got,
                     tc.area2);
    }
    return {false};
}

static vector<Claim> readClaims(InStream& stream, int caseCount) {
    vector<Claim> claims;
    claims.reserve(caseCount);
    for (int caseNo = 1; caseNo <= caseCount; ++caseNo) {
        claims.push_back(readCaseClaim(stream, caseNo));
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after case %d", caseCount);
    }
    return claims;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int caseCount = inf.readInt();
    tests.reserve(caseCount);
    for (int i = 0; i < caseCount; ++i) {
        int n = inf.readInt();
        int m = inf.readInt();
        long long area2 = inf.readLong();
        tests.push_back({n, m, area2});
    }

    vector<Claim> jury = readClaims(ans, caseCount);
    vector<Claim> participant = readClaims(ouf, caseCount);

    for (int i = 0; i < caseCount; ++i) {
        if (!jury[i].impossible && participant[i].impossible) {
            quitf(_wa, "case %d is possible in jury output but participant printed IMPOSSIBLE", i + 1);
        }
        if (jury[i].impossible && !participant[i].impossible) {
            quitf(_fail, "case %d has a valid participant witness while jury printed IMPOSSIBLE", i + 1);
        }
    }

    quitf(_ok, "%d case(s) validated", caseCount);
}
