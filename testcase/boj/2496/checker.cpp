#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x;
    long long y;
};

struct Claim {
    long long x;
    long long y;
    int count;
};

long long n, m, k;
vector<Point> diamonds;

int coveredCount(long long x, long long y) {
    int count = 0;
    long long radius = k / 2;
    for (const Point& p : diamonds) {
        if (llabs(p.x - x) + llabs(p.y - y) <= radius) {
            ++count;
        }
    }
    return count;
}

Claim readClaim(InStream& stream) {
    long long x = stream.readLong(0, n, "X");
    stream.readSpace();
    long long y = stream.readLong(0, m, "Y");
    stream.readEoln();

    int claimed = stream.readInt(0, static_cast<int>(diamonds.size()), "covered count");
    stream.readEoln();
    stream.readEof();

    int actual = coveredCount(x, y);
    if (claimed != actual) {
        stream.quitf(_wa,
                     "claimed count %d does not match center (%lld, %lld), which covers %d diamonds",
                     claimed,
                     x,
                     y,
                     actual);
    }
    return {x, y, claimed};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t;
    n = inf.readLong(1LL, 1000000LL, "N");
    inf.readSpace();
    m = inf.readLong(1LL, 1000000LL, "M");
    inf.readSpace();
    t = inf.readInt(1, 100, "T");
    inf.readSpace();
    k = inf.readLong(2LL, 10000000LL, "K");
    inf.readEoln();

    diamonds.reserve(t);
    for (int i = 0; i < t; ++i) {
        long long a = inf.readLong(0, n, format("A[%d]", i + 1).c_str());
        inf.readSpace();
        long long b = inf.readLong(0, m, format("B[%d]", i + 1).c_str());
        inf.readEoln();
        diamonds.push_back({a, b});
    }
    inf.readEof();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.count < jury.count) {
        quitf(_wa,
              "participant covers fewer diamonds than jury: participant=%d jury=%d",
              participant.count,
              jury.count);
    }
    if (participant.count > jury.count) {
        quitf(_fail,
              "participant covers more diamonds than jury: participant=%d jury=%d",
              participant.count,
              jury.count);
    }
    quitf(_ok, "covered diamonds: %d", participant.count);
}
