#include "testlib.h"

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

struct TestCase {
    long long n;
    long long m;
    long long area2;
};

struct Point {
    long long x;
    long long y;
};

struct Claim {
    bool impossible;
};

static vector<TestCase> cases;

static long long doubledArea(const vector<Point>& points) {
    long long cross = points[0].x * (points[1].y - points[2].y) +
                      points[1].x * (points[2].y - points[0].y) +
                      points[2].x * (points[0].y - points[1].y);
    return llabs(cross);
}

static void readCasePrefix(InStream& stream, int caseNo) {
    string token = stream.readToken();
    string expected = "Case #" + toString(caseNo) + ":";
    if (token == expected) {
        return;
    }

    if (token == "Case") {
        string number = stream.readToken();
        string expectedNumber = "#" + toString(caseNo) + ":";
        if (number == expectedNumber) {
            return;
        }
        stream.quitf(_wa,
                     "case %d: expected prefix \"%s\", found \"Case %s\"",
                     caseNo,
                     expected.c_str(),
                     number.c_str());
    }

    stream.quitf(_wa,
                 "case %d: expected prefix \"%s\", found \"%s\"",
                 caseNo,
                 expected.c_str(),
                 token.c_str());
}

static Claim readClaim(InStream& stream, int caseNo) {
    readCasePrefix(stream, caseNo);

    string first = stream.readToken();
    if (first == "IMPOSSIBLE") {
        return {true};
    }

    const TestCase& input = cases[caseNo - 1];
    vector<Point> points(3);
    points[0].x = stringToLongLong(stream, first);
    if (points[0].x < 0 || points[0].x > input.n) {
        stream.quitf(_wa,
                     "case %d: x_1 is %lld, expected 0..%lld",
                     caseNo,
                     points[0].x,
                     input.n);
    }
    points[0].y = stream.readLong(0LL, input.m, format("case %d y_1", caseNo).c_str());
    for (int i = 1; i < 3; ++i) {
        points[i].x = stream.readLong(0LL, input.n, format("case %d x_%d", caseNo, i + 1).c_str());
        points[i].y = stream.readLong(0LL, input.m, format("case %d y_%d", caseNo, i + 1).c_str());
    }

    long long actualArea2 = doubledArea(points);
    if (actualArea2 != input.area2) {
        stream.quitf(_wa,
                     "case %d: doubled area is %lld, expected %lld",
                     caseNo,
                     actualArea2,
                     input.area2);
    }

    return {false};
}

static vector<Claim> readClaims(InStream& stream, int caseCount) {
    vector<Claim> claims;
    claims.reserve(caseCount);
    for (int caseNo = 1; caseNo <= caseCount; ++caseNo) {
        claims.push_back(readClaim(stream, caseNo));
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after case %d", caseCount);
    }
    return claims;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int caseCount = inf.readInt();
    cases.reserve(caseCount);
    for (int i = 0; i < caseCount; ++i) {
        long long n = inf.readLong();
        long long m = inf.readLong();
        long long area2 = inf.readLong();
        cases.push_back({n, m, area2});
    }

    vector<Claim> jury = readClaims(ans, caseCount);
    vector<Claim> participant = readClaims(ouf, caseCount);

    for (int i = 0; i < caseCount; ++i) {
        int caseNo = i + 1;
        if (!jury[i].impossible && participant[i].impossible) {
            quitf(_wa, "case %d: participant printed IMPOSSIBLE but jury has a valid triangle", caseNo);
        }
        if (jury[i].impossible && !participant[i].impossible) {
            quitf(_fail, "case %d: participant found a valid triangle while jury printed IMPOSSIBLE", caseNo);
        }
    }

    quitf(_ok, "%d case(s) validated", caseCount);
}
