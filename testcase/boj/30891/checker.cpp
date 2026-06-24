#include "testlib.h"

#include <vector>

using namespace std;

struct Point {
    long long x;
    long long y;
};

int n;
long long r;
vector<Point> points;

struct Answer {
    long long x;
    long long y;
    int covered;
};

int countCovered(long long centerX, long long centerY) {
    int covered = 0;
    const __int128 limit = static_cast<__int128>(r) * r;
    for (const Point& point : points) {
        __int128 dx = static_cast<__int128>(centerX) - point.x;
        __int128 dy = static_cast<__int128>(centerY) - point.y;
        if (dx * dx + dy * dy <= limit) {
            ++covered;
        }
    }
    return covered;
}

Answer readAnswer(InStream& stream) {
    long long x = stream.readLong();
    long long y = stream.readLong();
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after center coordinates");
    }
    return {x, y, countCovered(x, y)};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    r = inf.readLong();
    points.resize(n);
    for (int i = 0; i < n; ++i) {
        points[i].x = inf.readLong();
        points[i].y = inf.readLong();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.covered < jury.covered) {
        quitf(_wa,
              "jury covers more rice grains: jury=(%lld, %lld) covers %d, participant=(%lld, %lld) covers %d",
              jury.x,
              jury.y,
              jury.covered,
              participant.x,
              participant.y,
              participant.covered);
    }
    if (participant.covered > jury.covered) {
        quitf(_fail,
              "participant found a better center: jury=(%lld, %lld) covers %d, participant=(%lld, %lld) covers %d",
              jury.x,
              jury.y,
              jury.covered,
              participant.x,
              participant.y,
              participant.covered);
    }

    quitf(_ok,
          "center (%lld, %lld) covers %d rice grains",
          participant.x,
          participant.y,
          participant.covered);
}
