#include "testlib.h"

#include <algorithm>
#include <array>
#include <map>
#include <queue>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int len;
    char dir;
};

struct Point {
    long long x;
    long long y;

    bool operator<(const Point& other) const {
        return tie(x, y) < tie(other.x, other.y);
    }
};

struct Interval {
    long long lo;
    long long hi;
    int edgeIndex;
};

struct Fenwick {
    vector<int> tree;

    explicit Fenwick(int n) : tree(n + 1, 0) {}

    void add(int index, int value) {
        for (int i = index; i < (int)tree.size(); i += i & -i) {
            tree[i] += value;
        }
    }

    int sumPrefix(int index) const {
        int result = 0;
        for (int i = index; i > 0; i -= i & -i) {
            result += tree[i];
        }
        return result;
    }

    int sumRange(int left, int right) const {
        if (left > right) return 0;
        return sumPrefix(right) - sumPrefix(left - 1);
    }
};

int dirIndex(char c) {
    if (c == 'N') return 0;
    if (c == 'E') return 1;
    if (c == 'S') return 2;
    return 3;
}

int oppositeDir(int d) {
    return d ^ 2;
}

Point movePoint(Point p, int len, char dir) {
    if (dir == 'N') p.y += len;
    if (dir == 'E') p.x += len;
    if (dir == 'S') p.y -= len;
    if (dir == 'W') p.x -= len;
    return p;
}

bool containsInterior(const vector<Interval>& intervals, long long value) {
    int lo = 0;
    int hi = (int)intervals.size() - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (intervals[mid].hi <= value) {
            lo = mid + 1;
        } else if (intervals[mid].lo >= value) {
            hi = mid - 1;
        } else {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 40000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 39999, "M");
    inf.readEoln();

    // CHECK: The statement says precisely one path links every pair of farms,
    // which makes the road graph a connected tree.
    ensuref(m == n - 1, "road graph must be a tree, got N=%d and M=%d", n, m);

    vector<Edge> edges(m);
    vector<vector<pair<int, int>>> graph(n + 1);
    set<pair<int, int>> seenEdges;
    vector<array<int, 4>> usedDirection(n + 1);
    for (int i = 1; i <= n; ++i) {
        usedDirection[i].fill(0);
    }

    for (int i = 0; i < m; ++i) {
        int f1 = inf.readInt(1, n, "F1");
        inf.readSpace();
        int f2 = inf.readInt(1, n, "F2");
        inf.readSpace();
        int len = inf.readInt(1, 1000, "L");
        inf.readSpace();
        string dToken = inf.readToken("N|E|S|W", "D");
        inf.readEoln();

        ensuref(f1 != f2, "road %d is a loop at farm %d", i + 1, f1);
        ensuref(seenEdges.insert(minmax(f1, f2)).second,
                "duplicate road %d between farms %d and %d", i + 1, f1, f2);

        int d = dirIndex(dToken[0]);
        ensuref(!usedDirection[f1][d],
                "farm %d has multiple roads in direction %c", f1, dToken[0]);
        usedDirection[f1][d] = 1;
        int od = oppositeDir(d);
        ensuref(!usedDirection[f2][od],
                "farm %d has multiple roads opposite road %d", f2, i + 1);
        usedDirection[f2][od] = 1;

        edges[i] = {f1, f2, len, dToken[0]};
        graph[f1].push_back({f2, i});
        graph[f2].push_back({f1, i});
    }

    int k = inf.readInt(1, 10000, "K");
    inf.readEoln();
    for (int i = 0; i < k; ++i) {
        inf.readInt(1, n, "F1");
        inf.readSpace();
        inf.readInt(1, n, "F2");
        inf.readSpace();
        inf.readInt(1, m, "I");
        inf.readEoln();
    }
    inf.readEof();

    vector<Point> pos(n + 1);
    vector<int> visited(n + 1, 0);
    queue<int> q;
    visited[1] = 1;
    pos[1] = {0, 0};
    q.push(1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto [v, edgeIndex] : graph[u]) {
            const Edge& e = edges[edgeIndex];
            Point next = (u == e.u) ? movePoint(pos[u], e.len, e.dir)
                                    : movePoint(pos[u], e.len, "SWNE"[dirIndex(e.dir)]);
            if (!visited[v]) {
                visited[v] = 1;
                pos[v] = next;
                q.push(v);
            } else {
                ensuref(pos[v].x == next.x && pos[v].y == next.y,
                        "inconsistent coordinates for farm %d", v);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        ensuref(visited[i], "farm %d is not connected to farm 1", i);
    }

    map<Point, int> farmsAt;
    for (int i = 1; i <= n; ++i) {
        ensuref(farmsAt.insert({pos[i], i}).second,
                "farms %d and %d occupy the same point", farmsAt[pos[i]], i);
    }

    map<long long, vector<Interval>> horizontalByY;
    map<long long, vector<Interval>> verticalByX;
    for (int i = 0; i < m; ++i) {
        Point a = pos[edges[i].u];
        Point b = pos[edges[i].v];
        if (a.y == b.y) {
            horizontalByY[a.y].push_back({min(a.x, b.x), max(a.x, b.x), i + 1});
        } else {
            ensuref(a.x == b.x, "road %d is not axis-aligned", i + 1);
            verticalByX[a.x].push_back({min(a.y, b.y), max(a.y, b.y), i + 1});
        }
    }

    auto validateDisjointIntervals = [](map<long long, vector<Interval>>& groups, const char* label) {
        for (auto& [line, intervals] : groups) {
            sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
                return tie(a.lo, a.hi, a.edgeIndex) < tie(b.lo, b.hi, b.edgeIndex);
            });
            for (int i = 1; i < (int)intervals.size(); ++i) {
                ensuref(intervals[i - 1].hi <= intervals[i].lo,
                        "%s roads %d and %d overlap on coordinate %lld",
                        label, intervals[i - 1].edgeIndex, intervals[i].edgeIndex, line);
            }
        }
    };

    validateDisjointIntervals(horizontalByY, "horizontal");
    validateDisjointIntervals(verticalByX, "vertical");

    for (int farm = 1; farm <= n; ++farm) {
        auto hIt = horizontalByY.find(pos[farm].y);
        if (hIt != horizontalByY.end()) {
            ensuref(!containsInterior(hIt->second, pos[farm].x),
                    "farm %d lies in the interior of a horizontal road", farm);
        }
        auto vIt = verticalByX.find(pos[farm].x);
        if (vIt != verticalByX.end()) {
            ensuref(!containsInterior(vIt->second, pos[farm].y),
                    "farm %d lies in the interior of a vertical road", farm);
        }
    }

    vector<long long> yValues;
    for (const auto& [y, intervals] : horizontalByY) {
        yValues.push_back(y);
    }
    sort(yValues.begin(), yValues.end());

    map<long long, vector<int>> addHorizontal;
    map<long long, vector<int>> removeHorizontal;
    for (const auto& [y, intervals] : horizontalByY) {
        int yIndex = (int)(lower_bound(yValues.begin(), yValues.end(), y) - yValues.begin()) + 1;
        for (const Interval& h : intervals) {
            if (h.lo + 1 <= h.hi - 1) {
                addHorizontal[h.lo + 1].push_back(yIndex);
                removeHorizontal[h.hi].push_back(yIndex);
            }
        }
    }

    set<long long> eventX;
    for (const auto& [x, intervals] : verticalByX) {
        eventX.insert(x);
    }
    for (const auto& [x, values] : addHorizontal) {
        eventX.insert(x);
    }
    for (const auto& [x, values] : removeHorizontal) {
        eventX.insert(x);
    }

    Fenwick activeHorizontal((int)yValues.size());
    for (long long x : eventX) {
        for (int yIndex : addHorizontal[x]) {
            activeHorizontal.add(yIndex, 1);
        }
        auto vIt = verticalByX.find(x);
        if (vIt != verticalByX.end()) {
            for (const Interval& v : vIt->second) {
                auto first = upper_bound(yValues.begin(), yValues.end(), v.lo);
                auto last = lower_bound(yValues.begin(), yValues.end(), v.hi);
                int left = (int)(first - yValues.begin()) + 1;
                int right = (int)(last - yValues.begin());
                ensuref(activeHorizontal.sumRange(left, right) == 0,
                        "vertical road %d crosses a horizontal road away from a farm",
                        v.edgeIndex);
            }
        }
        for (int yIndex : removeHorizontal[x]) {
            activeHorizontal.add(yIndex, -1);
        }
    }
}
