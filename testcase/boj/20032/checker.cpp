#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

struct Point {
    long long x;
    long long y;
};

struct Edge {
    int u;
    int v;
};

struct DSU {
    vector<int> parent;

    explicit DSU(int n) : parent(n + 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            parent[b] = a;
        }
    }
};

int n;
vector<Point> points;

long long cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool between(long long a, long long b, long long c) {
    return min(a, b) <= c && c <= max(a, b);
}

bool onSegment(const Point& a, const Point& b, const Point& p) {
    return cross(a, b, p) == 0 && between(a.x, b.x, p.x) && between(a.y, b.y, p.y);
}

bool segmentsIntersect(const Point& a, const Point& b, const Point& c, const Point& d) {
    long long c1 = cross(a, b, c);
    long long c2 = cross(a, b, d);
    long long c3 = cross(c, d, a);
    long long c4 = cross(c, d, b);

    if (c1 == 0 && onSegment(a, b, c)) {
        return true;
    }
    if (c2 == 0 && onSegment(a, b, d)) {
        return true;
    }
    if (c3 == 0 && onSegment(c, d, a)) {
        return true;
    }
    if (c4 == 0 && onSegment(c, d, b)) {
        return true;
    }
    return (c1 > 0) != (c2 > 0) && (c3 > 0) != (c4 > 0);
}

bool shareEndpoint(const Edge& a, const Edge& b) {
    return a.u == b.u || a.u == b.v || a.v == b.u || a.v == b.v;
}

bool sameUndirectedEdge(const Edge& a, const Edge& b) {
    return (a.u == b.u && a.v == b.v) || (a.u == b.v && a.v == b.u);
}

bool allowedEndpointIntersection(const Edge& a, const Edge& b) {
    if (!shareEndpoint(a, b) || sameUndirectedEdge(a, b)) {
        return false;
    }

    const Point& au = points[a.u];
    const Point& av = points[a.v];
    const Point& bu = points[b.u];
    const Point& bv = points[b.v];

    if (cross(au, av, bu) != 0 || cross(au, av, bv) != 0) {
        return true;
    }

    if (a.u != b.u && a.u != b.v && onSegment(bu, bv, au)) {
        return false;
    }
    if (a.v != b.u && a.v != b.v && onSegment(bu, bv, av)) {
        return false;
    }
    if (b.u != a.u && b.u != a.v && onSegment(au, av, bu)) {
        return false;
    }
    if (b.v != a.u && b.v != a.v && onSegment(au, av, bv)) {
        return false;
    }
    return true;
}

void validateSide(InStream& stream, const vector<Edge>& edges, const char* sideName) {
    DSU dsu(n);
    for (const Edge& edge : edges) {
        dsu.unite(edge.u, edge.v);
    }

    int root = dsu.find(1);
    for (int vertex = 2; vertex <= n; ++vertex) {
        if (dsu.find(vertex) != root) {
            stream.quitf(_wa, "%s side does not connect vertex %d to vertex 1", sideName, vertex);
        }
    }

    for (int i = 0; i < (int)edges.size(); ++i) {
        for (int j = i + 1; j < (int)edges.size(); ++j) {
            if (!segmentsIntersect(points[edges[i].u], points[edges[i].v],
                                   points[edges[j].u], points[edges[j].v])) {
                continue;
            }
            if (allowedEndpointIntersection(edges[i], edges[j])) {
                continue;
            }
            stream.quitf(_wa,
                         "%s side edges %d-%d and %d-%d intersect outside a common endpoint",
                         sideName, edges[i].u, edges[i].v, edges[j].u, edges[j].v);
        }
    }
}

struct Answer {
    int k;
};

Answer readAnswer(InStream& stream) {
    int k = stream.readInt(2, 2 * n - 1, "k");
    stream.readEoln();

    vector<int> sequence(k);
    for (int i = 0; i < k; ++i) {
        if (i > 0) {
            stream.readSpace();
        }
        sequence[i] = stream.readInt(1, n, format("s[%d]", i + 1).c_str());
        if (i > 0 && sequence[i - 1] == sequence[i]) {
            stream.quitf(_wa, "s[%d] and s[%d] are both %d", i, i + 1, sequence[i]);
        }
    }
    stream.readEoln();
    stream.readEof();

    vector<Edge> front;
    vector<Edge> back;
    for (int i = 0; i + 1 < k; i += 2) {
        front.push_back({sequence[i], sequence[i + 1]});
    }
    for (int i = 1; i + 1 < k; i += 2) {
        back.push_back({sequence[i], sequence[i + 1]});
    }

    validateSide(stream, front, "front");
    validateSide(stream, back, "back");
    return {k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    points.assign(n + 1, {});
    for (int i = 1; i <= n; ++i) {
        points[i].x = inf.readLong();
        points[i].y = inf.readLong();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.k > jury.k) {
        quitf(_wa, "jury has shorter sequence: jury=%d participant=%d", jury.k, participant.k);
    }
    if (participant.k < jury.k) {
        quitf(_fail, "participant found shorter valid sequence: jury=%d participant=%d", jury.k, participant.k);
    }
    quitf(_ok, "valid sequence length %d", participant.k);
}
