#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Segment {
    int x1;
    int y1;
    int x2;
    int y2;
};

struct Claim {
    bool none;
    int x1;
    int y1;
    int x2;
    int y2;

    int area() const {
        return (x2 - x1) * (y2 - y1);
    }
};

vector<Segment> segments;
bool horizontalEdge[101][101];
bool verticalEdge[101][101];

int low(int a, int b) {
    return min(a, b);
}

int high(int a, int b) {
    return max(a, b);
}

bool intervalIntersectsOpen(int a, int b, int lo, int hi) {
    return max(low(a, b), lo) < min(high(a, b), hi);
}

bool hasBottomOrTopSide(int y, int x1, int x2) {
    for (int x = x1; x < x2; ++x) {
        if (!horizontalEdge[x][y]) {
            return false;
        }
    }
    return true;
}

bool hasLeftOrRightSide(int x, int y1, int y2) {
    for (int y = y1; y < y2; ++y) {
        if (!verticalEdge[x][y]) {
            return false;
        }
    }
    return true;
}

bool hasInteriorPath(const Claim& claim) {
    for (const Segment& segment : segments) {
        if (segment.y1 == segment.y2) {
            int y = segment.y1;
            if (claim.y1 < y && y < claim.y2 &&
                intervalIntersectsOpen(segment.x1, segment.x2, claim.x1, claim.x2)) {
                return true;
            }
        } else {
            int x = segment.x1;
            if (claim.x1 < x && x < claim.x2 &&
                intervalIntersectsOpen(segment.y1, segment.y2, claim.y1, claim.y2)) {
                return true;
            }
        }
    }
    return false;
}

bool isValidRectangle(const Claim& claim) {
    return hasBottomOrTopSide(claim.y1, claim.x1, claim.x2) &&
           hasBottomOrTopSide(claim.y2, claim.x1, claim.x2) &&
           hasLeftOrRightSide(claim.x1, claim.y1, claim.y2) &&
           hasLeftOrRightSide(claim.x2, claim.y1, claim.y2) &&
           !hasInteriorPath(claim);
}

Claim readClaim(InStream& stream) {
    int first = stream.readInt(0, 100, "first token");
    if (first == 0) {
        stream.readEoln();
        stream.readEof();
        return {true, 0, 0, 0, 0};
    }

    int y1 = stream.readInt(1, 100, "lower-left y");
    stream.readEoln();
    int x2 = stream.readInt(1, 100, "upper-right x");
    int y2 = stream.readInt(1, 100, "upper-right y");
    stream.readEoln();
    stream.readEof();

    Claim claim{false, first, y1, x2, y2};
    if (claim.x1 >= claim.x2 || claim.y1 >= claim.y2) {
        stream.quitf(_wa, "rectangle corners are not lower-left and upper-right: (%d, %d) (%d, %d)",
                     claim.x1, claim.y1, claim.x2, claim.y2);
    }
    if (!isValidRectangle(claim)) {
        stream.quitf(_wa, "rectangle (%d, %d)-(%d, %d) is not a simple rectangle in the path",
                     claim.x1, claim.y1, claim.x2, claim.y2);
    }
    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    memset(horizontalEdge, 0, sizeof(horizontalEdge));
    memset(verticalEdge, 0, sizeof(verticalEdge));

    int x = inf.readInt();
    int y = inf.readInt();
    int n = inf.readInt();
    for (int i = 0; i < n; ++i) {
        string dir = inf.readToken();
        int distance = inf.readInt();

        int nx = x;
        int ny = y;
        if (dir == "U") {
            ny += distance;
        } else if (dir == "D") {
            ny -= distance;
        } else if (dir == "R") {
            nx += distance;
        } else {
            nx -= distance;
        }

        segments.push_back({x, y, nx, ny});
        if (y == ny) {
            for (int ex = low(x, nx); ex < high(x, nx); ++ex) {
                horizontalEdge[ex][y] = true;
            }
        } else {
            for (int ey = low(y, ny); ey < high(y, ny); ++ey) {
                verticalEdge[x][ey] = true;
            }
        }
        x = nx;
        y = ny;
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.none) {
        if (participant.none) {
            quitf(_ok, "no simple rectangle");
        }
        quitf(_fail, "participant found a valid rectangle while jury output is 0");
    }
    if (participant.none) {
        quitf(_wa, "participant output is 0, but jury has area %d", jury.area());
    }

    if (participant.area() < jury.area()) {
        quitf(_fail, "participant found smaller area: jury=%d participant=%d",
              jury.area(), participant.area());
    }
    if (participant.area() > jury.area()) {
        quitf(_wa, "participant area is larger than jury area: jury=%d participant=%d",
              jury.area(), participant.area());
    }

    quitf(_ok, "minimum simple rectangle area is %d", participant.area());
}
