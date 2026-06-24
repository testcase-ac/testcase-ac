#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

const long long MIN_COORD = -10000000LL;
const long long MAX_COORD = 10000000LL;

struct Point {
    long long x;
    long long y;
};

struct Answer {
    Point a;
    Point b;
    long long dist2;
};

long long squaredDistance(const Point& a, const Point& b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    return dx * dx + dy * dy;
}

Answer readAnswer(InStream& stream, int tc, const set<pair<long long, long long>>& cities) {
    Point a;
    Point b;
    a.x = stream.readLong(MIN_COORD, MAX_COORD, format("case %d x1", tc));
    a.y = stream.readLong(MIN_COORD, MAX_COORD, format("case %d y1", tc));
    b.x = stream.readLong(MIN_COORD, MAX_COORD, format("case %d x2", tc));
    b.y = stream.readLong(MIN_COORD, MAX_COORD, format("case %d y2", tc));

    if (!cities.count({a.x, a.y})) {
        stream.quitf(_wa, "case %d: first point (%lld, %lld) is not a city", tc, a.x, a.y);
    }
    if (!cities.count({b.x, b.y})) {
        stream.quitf(_wa, "case %d: second point (%lld, %lld) is not a city", tc, b.x, b.y);
    }
    if (a.x == b.x && a.y == b.y) {
        stream.quitf(_wa, "case %d: the same city is printed twice", tc);
    }

    return {a, b, squaredDistance(a, b)};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int T = inf.readInt();
    vector<set<pair<long long, long long>>> cases(T);

    for (int tc = 1; tc <= T; ++tc) {
        int n = inf.readInt();
        for (int i = 0; i < n; ++i) {
            long long x = inf.readLong();
            long long y = inf.readLong();
            cases[tc - 1].insert({x, y});
        }
    }

    for (int tc = 1; tc <= T; ++tc) {
        Answer jury = readAnswer(ans, tc, cases[tc - 1]);
        Answer participant = readAnswer(ouf, tc, cases[tc - 1]);

        if (participant.dist2 < jury.dist2) {
            quitf(_wa,
                  "case %d: jury has farther pair, jury distance squared=%lld, participant distance squared=%lld",
                  tc,
                  jury.dist2,
                  participant.dist2);
        }
        if (participant.dist2 > jury.dist2) {
            quitf(_fail,
                  "case %d: participant found farther pair, jury distance squared=%lld, participant distance squared=%lld",
                  tc,
                  jury.dist2,
                  participant.dist2);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }

    quitf(_ok, "all %d test cases have farthest pairs matching the jury distance", T);
}
