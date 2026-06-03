#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using Point = pair<ll, ll>;

const ll LIM = 1000000000LL;

ll randomCoord(ll span) {
    return rnd.next(-span, span);
}

void addRandomDuplicates(vector<Point>& points, int targetSize) {
    while ((int)points.size() < targetSize) {
        if (!points.empty() && rnd.next(100) < 35) {
            points.push_back(rnd.any(points));
        } else {
            ll span = rnd.any(vector<ll>{5, 20, 1000, LIM});
            points.push_back({randomCoord(span), randomCoord(span)});
        }
    }
}

vector<Point> makeDuplicateHeavy(int n) {
    int distinct = rnd.next(1, min(n, 5));
    vector<Point> base;
    for (int i = 0; i < distinct; ++i) {
        ll span = rnd.any(vector<ll>{0, 3, 100, LIM});
        base.push_back({randomCoord(span), randomCoord(span)});
    }

    vector<Point> points;
    for (int i = 0; i < n; ++i) {
        points.push_back(rnd.any(base));
    }
    return points;
}

vector<Point> makeLineCase(int n) {
    vector<Point> points;
    ll span = rnd.any(vector<ll>{10, 1000, LIM});
    for (int i = 0; i < n; ++i) {
        ll x = randomCoord(span);
        if (rnd.next(100) < 25 && !points.empty()) {
            x = rnd.any(points).first;
        }
        points.push_back({x, 0});
    }
    return points;
}

vector<Point> makeExtremeCase(int n) {
    vector<Point> corners = {
        {-LIM, -LIM},
        {-LIM, LIM},
        {LIM, -LIM},
        {LIM, LIM},
        {0, 0},
        {-LIM, 0},
        {LIM, 0},
        {0, -LIM},
        {0, LIM},
    };

    vector<Point> points;
    while ((int)points.size() < n && rnd.next(100) < 80) {
        points.push_back(rnd.any(corners));
    }
    addRandomDuplicates(points, n);
    return points;
}

vector<Point> makeGridCase(int n) {
    vector<ll> xs, ys;
    int xCount = rnd.next(2, min(5, n));
    int yCount = rnd.next(2, min(5, n));
    for (int i = 0; i < xCount; ++i) xs.push_back(randomCoord(20));
    for (int i = 0; i < yCount; ++i) ys.push_back(randomCoord(20));

    vector<Point> points;
    for (int i = 0; i < n; ++i) {
        points.push_back({rnd.any(xs), rnd.any(ys)});
    }
    return points;
}

vector<Point> makeClusterCase(int n) {
    vector<Point> centers;
    int centerCount = rnd.next(1, min(4, n));
    for (int i = 0; i < centerCount; ++i) {
        centers.push_back({randomCoord(1000), randomCoord(1000)});
    }

    vector<Point> points;
    for (int i = 0; i < n; ++i) {
        Point c = rnd.any(centers);
        ll dx = rnd.next(-3, 3);
        ll dy = rnd.next(-3, 3);
        points.push_back({c.first + dx, c.second + dy});
    }
    return points;
}

vector<Point> makeGeneralCase(int n) {
    vector<Point> points;
    ll span = rnd.any(vector<ll>{3, 50, 10000, LIM});
    addRandomDuplicates(points, n);
    if (rnd.next(100) < 50) {
        shuffle(points.begin(), points.end());
    }
    for (Point& p : points) {
        if (span != LIM) {
            p.first = max(-LIM, min(LIM, p.first + randomCoord(span)));
            p.second = max(-LIM, min(LIM, p.second + randomCoord(span)));
        }
    }
    return points;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, rnd.any(vector<int>{3, 5, 8, 12, 20, 40}));

    vector<Point> points;
    if (mode == 0) {
        points = makeDuplicateHeavy(n);
    } else if (mode == 1) {
        points = makeLineCase(n);
    } else if (mode == 2) {
        points = makeExtremeCase(n);
    } else if (mode == 3) {
        points = makeGridCase(n);
    } else if (mode == 4) {
        points = makeClusterCase(n);
    } else {
        points = makeGeneralCase(n);
    }

    if (rnd.next(100) < 50) {
        shuffle(points.begin(), points.end());
    }

    println(n);
    for (Point p : points) {
        println(p.first, p.second);
    }
}
