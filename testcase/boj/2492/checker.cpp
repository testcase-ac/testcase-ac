#include "testlib.h"

#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
};

struct Claim {
    int x;
    int y;
    int count;
};

int n, m, t, k;
vector<Point> jewels;

Claim readClaim(InStream& stream) {
    int x = stream.readInt(0, n - k, "X");
    stream.readSpace();
    int y = stream.readInt(k, m, "Y");
    stream.readEoln();
    int claimedCount = stream.readInt(0, t, "count");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after claimed count");
    }

    int actualCount = 0;
    for (const Point& jewel : jewels) {
        if (x <= jewel.x && jewel.x <= x + k &&
            y - k <= jewel.y && jewel.y <= y) {
            ++actualCount;
        }
    }

    if (claimedCount != actualCount) {
        stream.quitf(_wa,
                     "claimed count %d does not match square count %d for top-left (%d, %d)",
                     claimedCount,
                     actualCount,
                     x,
                     y);
    }

    return {x, y, claimedCount};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    t = inf.readInt();
    k = inf.readInt();

    jewels.resize(t);
    for (int i = 0; i < t; ++i) {
        jewels[i].x = inf.readInt();
        jewels[i].y = inf.readInt();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.count < jury.count) {
        quitf(_wa,
              "jury has better answer: jury=%d participant=%d",
              jury.count,
              participant.count);
    }
    if (participant.count > jury.count) {
        quitf(_fail,
              "participant found better answer: jury=%d participant=%d",
              jury.count,
              participant.count);
    }

    quitf(_ok, "answer=%d", participant.count);
}
