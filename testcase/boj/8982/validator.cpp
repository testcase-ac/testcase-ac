#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 5000, "N");
    inf.readEoln();
    ensuref(n % 2 == 0, "N must be even: %d", n);

    vector<Point> vertices(n);
    for (int i = 0; i < n; ++i) {
        vertices[i].x = inf.readInt(0, 40000, "x_i");
        inf.readSpace();
        vertices[i].y = inf.readInt(0, 40000, "y_i");
        inf.readEoln();
    }

    ensuref(vertices[0].x == 0 && vertices[0].y == 0,
            "first vertex must be (0, 0), found (%d, %d)",
            vertices[0].x,
            vertices[0].y);
    ensuref(vertices[n - 1].y == 0, "last vertex y-coordinate must be 0, found %d", vertices[n - 1].y);
    ensuref(vertices[n - 1].x > 0, "last vertex x-coordinate must be positive, found %d", vertices[n - 1].x);

    set<pair<int, int>> seenVertices;
    ensuref(seenVertices.insert({0, 0}).second, "duplicate vertex at index 1");

    set<pair<pair<int, int>, int>> horizontalSegments;
    for (int i = 1; i < n; ++i) {
        const Point& prev = vertices[i - 1];
        const Point& cur = vertices[i];

        ensuref(seenVertices.insert({cur.x, cur.y}).second,
                "duplicate vertex at index %d: (%d, %d)",
                i + 1,
                cur.x,
                cur.y);

        if (i % 2 == 1) {
            ensuref(prev.x == cur.x,
                    "segment %d must be vertical: (%d, %d) to (%d, %d)",
                    i,
                    prev.x,
                    prev.y,
                    cur.x,
                    cur.y);
            ensuref(prev.y != cur.y,
                    "segment %d must have positive vertical length at x=%d",
                    i,
                    cur.x);
        } else {
            ensuref(prev.y == cur.y,
                    "segment %d must be horizontal: (%d, %d) to (%d, %d)",
                    i,
                    prev.x,
                    prev.y,
                    cur.x,
                    cur.y);
            ensuref(prev.y > 0, "horizontal bottom segment %d must be below the top line", i);
            ensuref(prev.x < cur.x,
                    "horizontal bottom segment %d must go left-to-right: x %d to %d",
                    i,
                    prev.x,
                    cur.x);
            ensuref(horizontalSegments.insert({{prev.x, cur.x}, prev.y}).second,
                    "duplicate horizontal segment from (%d, %d) to (%d, %d)",
                    prev.x,
                    prev.y,
                    cur.x,
                    cur.y);
        }
    }

    int k = inf.readInt(1, n / 2, "K");
    inf.readEoln();

    set<pair<pair<int, int>, int>> holes;
    for (int i = 0; i < k; ++i) {
        int a = inf.readInt(0, 40000, "a_i");
        inf.readSpace();
        int b = inf.readInt(0, 40000, "b_i");
        inf.readSpace();
        int c = inf.readInt(0, 40000, "c_i");
        inf.readSpace();
        int d = inf.readInt(0, 40000, "d_i");
        inf.readEoln();

        ensuref(b == d, "hole %d endpoints must have the same y-coordinate: %d and %d", i + 1, b, d);
        ensuref(a < c, "hole %d must satisfy a < c, found %d and %d", i + 1, a, c);

        pair<pair<int, int>, int> segment = {{a, c}, b};
        ensuref(horizontalSegments.count(segment) == 1,
                "hole %d does not match an aquarium horizontal segment: (%d, %d) to (%d, %d)",
                i + 1,
                a,
                b,
                c,
                d);
        ensuref(holes.insert(segment).second,
                "multiple holes on the same horizontal segment: (%d, %d) to (%d, %d)",
                a,
                b,
                c,
                d);
    }

    inf.readEof();
}
