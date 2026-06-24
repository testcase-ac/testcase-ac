#include "testlib.h"

#include <algorithm>
#include <map>
#include <set>
#include <utility>
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

struct Placement {
    vector<Point> p;
};

int n;
vector<Edge> edges;
set<pair<int, int>> usedEdges;

void addEdge(int u, int v) {
    if (u > v) {
        swap(u, v);
    }
    if (usedEdges.insert({u, v}).second) {
        edges.push_back({u, v});
    }
}

long long cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool between(long long a, long long b, long long c) {
    return min(a, b) <= c && c <= max(a, b);
}

bool onSegment(const Point& a, const Point& b, const Point& c) {
    return cross(a, b, c) == 0 && between(a.x, b.x, c.x) && between(a.y, b.y, c.y);
}

bool boxesIntersect(const Point& a, const Point& b, const Point& c, const Point& d) {
    return max(min(a.x, b.x), min(c.x, d.x)) <= min(max(a.x, b.x), max(c.x, d.x)) &&
           max(min(a.y, b.y), min(c.y, d.y)) <= min(max(a.y, b.y), max(c.y, d.y));
}

bool segmentsIntersect(const Point& a, const Point& b, const Point& c, const Point& d) {
    if (!boxesIntersect(a, b, c, d)) {
        return false;
    }
    long long c1 = cross(a, b, c);
    long long c2 = cross(a, b, d);
    long long c3 = cross(c, d, a);
    long long c4 = cross(c, d, b);

    if (c1 == 0 && onSegment(a, b, c)) return true;
    if (c2 == 0 && onSegment(a, b, d)) return true;
    if (c3 == 0 && onSegment(c, d, a)) return true;
    if (c4 == 0 && onSegment(c, d, b)) return true;
    return (c1 > 0) != (c2 > 0) && (c3 > 0) != (c4 > 0);
}

bool samePoint(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}

bool shareStudent(const Edge& a, const Edge& b) {
    return a.u == b.u || a.u == b.v || a.v == b.u || a.v == b.v;
}

int sharedStudent(const Edge& a, const Edge& b) {
    if (a.u == b.u || a.u == b.v) return a.u;
    if (a.v == b.u || a.v == b.v) return a.v;
    return -1;
}

bool onlyIntersectAtSharedEndpoint(const Point& a,
                                   const Point& b,
                                   const Point& c,
                                   const Point& d,
                                   const Point& shared) {
    vector<Point> endpointHits;
    if (onSegment(a, b, c)) endpointHits.push_back(c);
    if (onSegment(a, b, d)) endpointHits.push_back(d);
    if (onSegment(c, d, a)) endpointHits.push_back(a);
    if (onSegment(c, d, b)) endpointHits.push_back(b);

    if (!endpointHits.empty()) {
        for (const Point& hit : endpointHits) {
            if (!samePoint(hit, shared)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

Placement readPlacement(InStream& stream) {
    Placement placement;
    placement.p.resize(n + 1);

    map<pair<long long, long long>, int> seen;
    for (int i = 1; i <= n; ++i) {
        long long x = stream.readLong(-1000000000LL, 1000000000LL,
                                      format("x[%d]", i).c_str());
        stream.readSpace();
        long long y = stream.readLong(-1000000000LL, 1000000000LL,
                                      format("y[%d]", i).c_str());
        stream.readEoln();

        auto inserted = seen.insert({{x, y}, i});
        if (!inserted.second) {
            stream.quitf(_wa,
                         "students %d and %d have the same position (%lld, %lld)",
                         inserted.first->second,
                         i,
                         x,
                         y);
        }
        placement.p[i] = {x, y};
    }
    stream.readEof();

    for (int i = 0; i < (int)edges.size(); ++i) {
        const Edge& first = edges[i];
        const Point& a = placement.p[first.u];
        const Point& b = placement.p[first.v];
        for (int j = i + 1; j < (int)edges.size(); ++j) {
            const Edge& second = edges[j];
            const Point& c = placement.p[second.u];
            const Point& d = placement.p[second.v];
            if (!segmentsIntersect(a, b, c, d)) {
                continue;
            }

            if (shareStudent(first, second)) {
                int student = sharedStudent(first, second);
                if (onlyIntersectAtSharedEndpoint(a, b, c, d, placement.p[student])) {
                    continue;
                }
            }

            stream.quitf(_wa,
                         "pass paths (%d, %d) and (%d, %d) overlap",
                         first.u,
                         first.v,
                         second.u,
                         second.v);
        }
    }

    return placement;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    int kobe = inf.readInt();
    int lebron = inf.readInt();
    int curry = inf.readInt();
    int jordan = inf.readInt();

    for (int i = 1; i < n; ++i) {
        addEdge(i, i + 1);
    }
    addEdge(n, 1);
    addEdge(kobe, lebron);
    addEdge(curry, jordan);

    readPlacement(ans);
    readPlacement(ouf);

    quitf(_ok, "valid placement");
}
