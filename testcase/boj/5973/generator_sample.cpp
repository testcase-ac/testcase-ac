#include "testlib.h"

#include <algorithm>
#include <map>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<long long, long long>;

const long long COORD_LIMIT = 1000000000LL;
const long long ANSWER_LIMIT = 2147483647LL;

long long bridgeCount(const vector<Point>& points) {
    map<Point, long long> pairSums;
    for (int i = 0; i < (int)points.size(); ++i) {
        for (int j = i + 1; j < (int)points.size(); ++j) {
            ++pairSums[{points[i].first + points[j].first,
                        points[i].second + points[j].second}];
        }
    }

    long long answer = 0;
    for (const auto& entry : pairSums) {
        long long count = entry.second;
        answer += count * (count - 1) / 2;
    }
    return answer;
}

bool inBounds(const Point& point) {
    return -COORD_LIMIT <= point.first && point.first <= COORD_LIMIT &&
           -COORD_LIMIT <= point.second && point.second <= COORD_LIMIT;
}

bool addPoint(vector<Point>& points, set<Point>& seen, Point point) {
    if (!inBounds(point) || seen.count(point)) {
        return false;
    }
    seen.insert(point);
    points.push_back(point);
    return true;
}

void addRandomPoint(vector<Point>& points, set<Point>& seen, int span) {
    while (true) {
        Point point = {rnd.next(-span, span), rnd.next(-span, span)};
        if (addPoint(points, seen, point)) {
            return;
        }
    }
}

bool addParallelogram(vector<Point>& points, set<Point>& seen, Point centerSum,
                      Point deltaA, Point deltaB) {
    vector<Point> candidate = {
        {centerSum.first - deltaA.first, centerSum.second - deltaA.second},
        {centerSum.first + deltaA.first, centerSum.second + deltaA.second},
        {centerSum.first - deltaB.first, centerSum.second - deltaB.second},
        {centerSum.first + deltaB.first, centerSum.second + deltaB.second},
    };

    set<Point> local(candidate.begin(), candidate.end());
    if (local.size() != candidate.size()) {
        return false;
    }
    for (const Point& point : candidate) {
        if (!inBounds(point) || seen.count(point)) {
            return false;
        }
    }
    for (const Point& point : candidate) {
        addPoint(points, seen, point);
    }
    return true;
}

vector<Point> makeCase() {
    int mode = rnd.next(0, 4);
    vector<Point> points;
    set<Point> seen;

    if (mode == 0) {
        int n = rnd.next(4, 30);
        int span = rnd.next(4, 80);
        while ((int)points.size() < n) {
            addRandomPoint(points, seen, span);
        }
    } else if (mode == 1) {
        int groups = rnd.next(1, 5);
        for (int g = 0; g < groups; ++g) {
            while (true) {
                Point centerSum = {rnd.next(-30, 30), rnd.next(-30, 30)};
                Point deltaA = {rnd.next(1, 15), rnd.next(-15, 15)};
                Point deltaB = {rnd.next(-15, 15), rnd.next(1, 15)};
                if (addParallelogram(points, seen, centerSum, deltaA, deltaB)) {
                    break;
                }
            }
        }
        int target = rnd.next((int)points.size(), min(40, (int)points.size() + 12));
        while ((int)points.size() < target) {
            addRandomPoint(points, seen, 100);
        }
    } else if (mode == 2) {
        Point centerSum = {rnd.next(-10, 10), rnd.next(-10, 10)};
        int pairCount = rnd.next(2, 11);
        for (int i = 1; i <= pairCount; ++i) {
            int dx = i * rnd.next(1, 3);
            int dy = rnd.next(-20, 20);
            addPoint(points, seen, {centerSum.first - dx, centerSum.second - dy});
            addPoint(points, seen, {centerSum.first + dx, centerSum.second + dy});
        }
        int extra = rnd.next(0, 8);
        while (extra--) {
            addRandomPoint(points, seen, 120);
        }
    } else if (mode == 3) {
        int n = rnd.next(4, 24);
        long long baseX = rnd.any(vector<long long>{-COORD_LIMIT, COORD_LIMIT - 1000, -1000, 0});
        long long baseY = rnd.any(vector<long long>{-COORD_LIMIT, COORD_LIMIT - 1000, -1000, 0});
        for (int i = 0; (int)points.size() < n; ++i) {
            Point point = {baseX + rnd.next(0, 1000), baseY + rnd.next(0, 1000)};
            addPoint(points, seen, point);
        }
    } else {
        int side = rnd.next(3, 8);
        for (int x = 0; x < side; ++x) {
            for (int y = 0; y < side; ++y) {
                if (rnd.next(0, 99) < 55) {
                    addPoint(points, seen, {x * 2LL, y * 2LL});
                }
            }
        }
        while ((int)points.size() < 4) {
            addRandomPoint(points, seen, 20);
        }
    }

    shuffle(points.begin(), points.end());
    return points;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Point> points;
    for (int attempt = 0; attempt < 1000; ++attempt) {
        points = makeCase();
        if (4 <= (int)points.size() && (int)points.size() <= 1000 &&
            bridgeCount(points) <= ANSWER_LIMIT) {
            break;
        }
    }

    println((int)points.size());
    for (const Point& point : points) {
        println(point.first, point.second);
    }
    return 0;
}
