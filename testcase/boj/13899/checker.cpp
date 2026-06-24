#include "testlib.h"

#include <vector>
using namespace std;

struct Edge {
    int a;
    int b;
    long long dx;
    long long dy;
};

struct Point {
    long long x;
    long long y;
};

int n, m;
vector<Edge> edges;

vector<Point> readAnswer(InStream& stream) {
    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        points[i].x = stream.readLong(-1000000000LL, 1000000000LL,
                                      format("x[%d]", i + 1).c_str());
        points[i].y = stream.readLong(-1000000000LL, 1000000000LL,
                                      format("y[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d coordinate pairs", n);
    }

    for (int i = 0; i < m; ++i) {
        const Edge& e = edges[i];
        long long actualDx = points[e.b].x - points[e.a].x;
        long long actualDy = points[e.b].y - points[e.a].y;
        if (actualDx != e.dx || actualDy != e.dy) {
            stream.quitf(_wa,
                         "constraint %d is violated: base %d to %d expected (%lld, %lld), found (%lld, %lld)",
                         i + 1, e.a + 1, e.b + 1, e.dx, e.dy, actualDx, actualDy);
        }
    }

    return points;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    edges.reserve(m);
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt();
        int b = inf.readInt();
        long long dx = inf.readLong();
        long long dy = inf.readLong();
        edges.push_back({a - 1, b - 1, dx, dy});
    }

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "coordinates satisfy all constraints");
}
