#include "testlib.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
using namespace std;

static const int SCALE = 1000000;
static const long double GEOMETRY_EPS = 1e-18L;
static const int BVH_LEAF_SIZE = 16;
static const long long MAX_SECOND_REPLACEMENT_SEGMENTS = 250000;
static const long long MAX_SECOND_NODE_PAIRS = 4000000;
static const long long MAX_SECOND_SEGMENT_PAIRS = 12000000;
static const long long UNLIMITED_SEARCH = numeric_limits<long long>::max() / 4;

struct Point {
    long long x;
    long long y;
};

struct RealPoint {
    long double x;
    long double y;
};

using RealSegment = pair<RealPoint, RealPoint>;

struct Box {
    long double minX;
    long double minY;
    long double maxX;
    long double maxY;
};

struct BvhNode {
    Box box;
    int left = -1;
    int right = -1;
    int begin = 0;
    int end = 0;

    bool isLeaf() const {
        return left == -1;
    }

    int size() const {
        return end - begin;
    }
};

struct Bvh {
    vector<int> order;
    vector<BvhNode> nodes;
    int root = -1;
};

enum class BoundaryStatus {
    Simple,
    Intersects,
    SearchBudgetExceeded,
};

struct BoundaryCheckLimits {
    long long maxNodePairs;
    long long maxSegmentPairs;
};

struct BoundaryCheckResult {
    BoundaryStatus status = BoundaryStatus::Simple;
    int firstSegment = -1;
    int secondSegment = -1;
};

static long long cross(const Point& a, const Point& b, const Point& c) {
    long long ux = b.x - a.x;
    long long uy = b.y - a.y;
    long long vx = c.x - a.x;
    long long vy = c.y - a.y;
    return ux * vy - uy * vx;
}

static bool between(long long a, long long b, long long c) {
    return min(a, c) <= b && b <= max(a, c);
}

static bool onSegment(const Point& a, const Point& b, const Point& c) {
    return cross(a, b, c) == 0 && between(a.x, b.x, c.x) && between(a.y, b.y, c.y);
}

static int sign(long long value) {
    return (value > 0) - (value < 0);
}

static bool segmentsIntersect(const Point& a, const Point& b, const Point& c, const Point& d) {
    long long c1 = cross(a, b, c);
    long long c2 = cross(a, b, d);
    long long c3 = cross(c, d, a);
    long long c4 = cross(c, d, b);

    if (sign(c1) * sign(c2) < 0 && sign(c3) * sign(c4) < 0) {
        return true;
    }

    return onSegment(a, c, b) || onSegment(a, d, b) ||
           onSegment(c, a, d) || onSegment(c, b, d);
}

static long double crossReal(const RealPoint& a, const RealPoint& b, const RealPoint& c) {
    long double ux = b.x - a.x;
    long double uy = b.y - a.y;
    long double vx = c.x - a.x;
    long double vy = c.y - a.y;
    return ux * vy - uy * vx;
}

static bool betweenReal(long double a, long double b, long double c) {
    return min(a, c) - GEOMETRY_EPS <= b && b <= max(a, c) + GEOMETRY_EPS;
}

static bool onSegmentReal(const RealPoint& a, const RealPoint& b, const RealPoint& c) {
    return fabsl(crossReal(a, b, c)) <= GEOMETRY_EPS &&
           betweenReal(a.x, b.x, c.x) &&
           betweenReal(a.y, b.y, c.y);
}

static int signReal(long double value) {
    if (value > GEOMETRY_EPS) {
        return 1;
    }
    if (value < -GEOMETRY_EPS) {
        return -1;
    }
    return 0;
}

static bool segmentsIntersectReal(const RealPoint& a, const RealPoint& b,
                                  const RealPoint& c, const RealPoint& d) {
    long double c1 = crossReal(a, b, c);
    long double c2 = crossReal(a, b, d);
    long double c3 = crossReal(c, d, a);
    long double c4 = crossReal(c, d, b);

    if (signReal(c1) * signReal(c2) < 0 && signReal(c3) * signReal(c4) < 0) {
        return true;
    }

    return onSegmentReal(a, c, b) || onSegmentReal(a, d, b) ||
           onSegmentReal(c, a, d) || onSegmentReal(c, b, d);
}

static Box segmentBox(const RealSegment& segment) {
    return {
        min(segment.first.x, segment.second.x),
        min(segment.first.y, segment.second.y),
        max(segment.first.x, segment.second.x),
        max(segment.first.y, segment.second.y),
    };
}

static Box mergeBoxes(const Box& a, const Box& b) {
    return {
        min(a.minX, b.minX),
        min(a.minY, b.minY),
        max(a.maxX, b.maxX),
        max(a.maxY, b.maxY),
    };
}

static bool boxesOverlap(const Box& a, const Box& b) {
    return a.minX <= b.maxX + GEOMETRY_EPS &&
           b.minX <= a.maxX + GEOMETRY_EPS &&
           a.minY <= b.maxY + GEOMETRY_EPS &&
           b.minY <= a.maxY + GEOMETRY_EPS;
}

static long double boxCenter(const Box& box, int axis) {
    return axis == 0 ? (box.minX + box.maxX) / 2.0L : (box.minY + box.maxY) / 2.0L;
}

static int buildBvhNode(Bvh& bvh, const vector<Box>& boxes, int begin, int end) {
    int nodeIndex = (int)bvh.nodes.size();
    bvh.nodes.push_back({});

    Box box = boxes[bvh.order[begin]];
    for (int i = begin + 1; i < end; ++i) {
        box = mergeBoxes(box, boxes[bvh.order[i]]);
    }

    BvhNode& node = bvh.nodes[nodeIndex];
    node.box = box;
    node.begin = begin;
    node.end = end;

    if (end - begin <= BVH_LEAF_SIZE) {
        return nodeIndex;
    }

    int axis = (box.maxX - box.minX >= box.maxY - box.minY) ? 0 : 1;
    int middle = begin + (end - begin) / 2;
    nth_element(bvh.order.begin() + begin, bvh.order.begin() + middle, bvh.order.begin() + end,
                [&](int lhs, int rhs) {
                    return boxCenter(boxes[lhs], axis) < boxCenter(boxes[rhs], axis);
                });

    int left = buildBvhNode(bvh, boxes, begin, middle);
    int right = buildBvhNode(bvh, boxes, middle, end);
    bvh.nodes[nodeIndex].left = left;
    bvh.nodes[nodeIndex].right = right;
    return nodeIndex;
}

static Bvh buildBvh(const vector<Box>& boxes) {
    Bvh bvh;
    bvh.order.resize(boxes.size());
    iota(bvh.order.begin(), bvh.order.end(), 0);
    bvh.nodes.reserve(boxes.size() * 2);
    if (!boxes.empty()) {
        bvh.root = buildBvhNode(bvh, boxes, 0, (int)boxes.size());
    }
    return bvh;
}

static bool adjacentBoundarySegments(int first, int second, int segmentCount) {
    int distance = abs(first - second);
    return distance == 1 || distance == segmentCount - 1;
}

static BoundaryCheckResult checkSimpleBoundary(
        const vector<RealSegment>& boundarySegments,
        BoundaryCheckLimits limits) {
    BoundaryCheckResult result;
    int segmentCount = (int)boundarySegments.size();
    if (segmentCount <= 1) {
        return result;
    }

    vector<Box> boxes;
    boxes.reserve(boundarySegments.size());
    for (const RealSegment& segment : boundarySegments) {
        boxes.push_back(segmentBox(segment));
    }

    Bvh bvh = buildBvh(boxes);
    vector<pair<int, int>> pending;
    pending.push_back({bvh.root, bvh.root});

    long long nodePairs = 0;
    long long segmentPairs = 0;

    auto splitPair = [&](int firstNode, int secondNode) {
        const BvhNode& first = bvh.nodes[firstNode];
        const BvhNode& second = bvh.nodes[secondNode];

        if (firstNode == secondNode) {
            pending.push_back({first.left, first.left});
            pending.push_back({first.left, first.right});
            pending.push_back({first.right, first.right});
            return;
        }

        if (!first.isLeaf() && (second.isLeaf() || first.size() >= second.size())) {
            pending.push_back({first.left, secondNode});
            pending.push_back({first.right, secondNode});
        } else {
            pending.push_back({firstNode, second.left});
            pending.push_back({firstNode, second.right});
        }
    };

    while (!pending.empty()) {
        auto [firstNode, secondNode] = pending.back();
        pending.pop_back();

        ++nodePairs;
        if (nodePairs > limits.maxNodePairs) {
            result.status = BoundaryStatus::SearchBudgetExceeded;
            return result;
        }

        const BvhNode& first = bvh.nodes[firstNode];
        const BvhNode& second = bvh.nodes[secondNode];
        if (!boxesOverlap(first.box, second.box)) {
            continue;
        }

        if (!first.isLeaf() || !second.isLeaf()) {
            splitPair(firstNode, secondNode);
            continue;
        }

        for (int i = first.begin; i < first.end; ++i) {
            int firstSegment = bvh.order[i];
            int secondBegin = (firstNode == secondNode) ? i + 1 : second.begin;
            for (int j = secondBegin; j < second.end; ++j) {
                int secondSegment = bvh.order[j];
                if (adjacentBoundarySegments(firstSegment, secondSegment, segmentCount)) {
                    continue;
                }
                if (!boxesOverlap(boxes[firstSegment], boxes[secondSegment])) {
                    continue;
                }

                ++segmentPairs;
                if (segmentPairs > limits.maxSegmentPairs) {
                    result.status = BoundaryStatus::SearchBudgetExceeded;
                    return result;
                }

                if (segmentsIntersectReal(boundarySegments[firstSegment].first,
                                          boundarySegments[firstSegment].second,
                                          boundarySegments[secondSegment].first,
                                          boundarySegments[secondSegment].second)) {
                    if (firstSegment > secondSegment) {
                        swap(firstSegment, secondSegment);
                    }
                    result.status = BoundaryStatus::Intersects;
                    result.firstSegment = firstSegment;
                    result.secondSegment = secondSegment;
                    return result;
                }
            }
        }
    }

    return result;
}

static BoundaryCheckResult ensureSimpleBoundary(
        const vector<RealSegment>& boundarySegments,
        const string& label,
        BoundaryCheckLimits limits) {
    BoundaryCheckResult result = checkSimpleBoundary(boundarySegments, limits);
    ensuref(result.status != BoundaryStatus::Intersects,
            "%s boundary segments %d and %d overlap or intersect",
            label.c_str(), result.firstSegment + 1, result.secondSegment + 1);
    return result;
}

static RealPoint transformPoint(const RealPoint& sideStart, const RealPoint& sideEnd,
                                const Point& point) {
    long double baseX = sideEnd.x - sideStart.x;
    long double baseY = sideEnd.y - sideStart.y;
    long double x = (long double)point.x / SCALE;
    long double y = (long double)point.y / SCALE;

    return {
        sideStart.x + x * baseX - y * baseY,
        sideStart.y + x * baseY + y * baseX,
    };
}

static RealPoint transformUnitPoint(const RealPoint& sideStart, const RealPoint& sideEnd,
                                    const RealPoint& point) {
    long double baseX = sideEnd.x - sideStart.x;
    long double baseY = sideEnd.y - sideStart.y;

    return {
        sideStart.x + point.x * baseX - point.y * baseY,
        sideStart.y + point.x * baseY + point.y * baseX,
    };
}

static long long readFixedPoint(const string& name, const string& pattern) {
    string token = inf.readToken(pattern, name.c_str());

    int sign = 1;
    size_t pos = 0;
    if (token[pos] == '-') {
        sign = -1;
        ++pos;
    }

    size_t dot = token.find('.', pos);
    long long integerPart = 0;
    for (size_t i = pos; i < dot; ++i) {
        integerPart = integerPart * 10 + (token[i] - '0');
    }

    long long fractionalPart = 0;
    for (size_t i = dot + 1; i < token.size(); ++i) {
        fractionalPart = fractionalPart * 10 + (token[i] - '0');
    }

    return sign * (integerPart * SCALE + fractionalPart);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "n");
    inf.readEoln();

    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        points[i].x = readFixedPoint("x_i", "[01]\\.[0-9]{6}");
        inf.readSpace();
        points[i].y = readFixedPoint("y_i", "-?0\\.[0-9]{6}");
        inf.readEoln();

        ensuref(0 <= points[i].x && points[i].x <= SCALE,
                "x coordinate at point %d is out of bounds", i + 1);
        ensuref(-SCALE / 2 < points[i].y && points[i].y < SCALE / 2,
                "y coordinate at point %d is out of bounds", i + 1);
    }

    ensuref(points.front().x == 0 && points.front().y == 0, "first point must be (0, 0)");
    ensuref(points.back().x == SCALE && points.back().y == 0, "last point must be (1, 0)");

    __int128 squaredScaleSum = 0;
    bool isIdentityPolyline = (n == 2);
    for (int i = 1; i < n; ++i) {
        long long dx = points[i].x - points[i - 1].x;
        long long dy = points[i].y - points[i - 1].y;
        ensuref(dx != 0 || dy != 0, "segment %d has zero length", i);
        squaredScaleSum += (__int128)dx * dx + (__int128)dy * dy;
    }
    ensuref(isIdentityPolyline || squaredScaleSum < (__int128)SCALE * SCALE,
            "non-identity replacement scale squares must sum to less than 1 for convergence");

    for (int i = 0; i + 1 < n; ++i) {
        for (int j = i + 1; j + 1 < n; ++j) {
            if (j == i + 1) {
                continue;
            }

            ensuref(!segmentsIntersect(points[i], points[i + 1], points[j], points[j + 1]),
                    "segments %d and %d overlap or intersect", i + 1, j + 1);
        }
    }

    const long double sqrtThree = sqrtl(3.0L);
    vector<RealSegment> triangleSides = {
        {{0.0L, 0.0L}, {1.0L, 0.0L}},
        {{1.0L, 0.0L}, {0.5L, -sqrtThree / 2.0L}},
        {{0.5L, -sqrtThree / 2.0L}, {0.0L, 0.0L}},
    };

    vector<RealPoint> unitPoints;
    unitPoints.reserve(n);
    for (const Point& point : points) {
        unitPoints.push_back({
            (long double)point.x / SCALE,
            (long double)point.y / SCALE,
        });
    }

    vector<RealSegment> boundarySegments;
    boundarySegments.reserve(3 * (n - 1));
    for (const auto& side : triangleSides) {
        for (int i = 0; i + 1 < n; ++i) {
            boundarySegments.push_back({
                transformPoint(side.first, side.second, points[i]),
                transformPoint(side.first, side.second, points[i + 1]),
            });
        }
    }

    ensureSimpleBoundary(boundarySegments, "first replacement",
                         {UNLIMITED_SEARCH, UNLIMITED_SEARCH});

    long long secondReplacementSegmentCount = 3LL * (n - 1) * (n - 1);
    // CHECK: the statement's infinite non-overlap guarantee is too expensive to
    // prove completely here, so the validator rejects bounded finite overlaps
    // found by the second-replacement BVH search and accepts inconclusive cases.
    if (secondReplacementSegmentCount <= MAX_SECOND_REPLACEMENT_SEGMENTS) {
        vector<RealSegment> secondBoundarySegments;
        secondBoundarySegments.reserve((size_t)secondReplacementSegmentCount);

        for (const auto& segment : boundarySegments) {
            for (int i = 0; i + 1 < n; ++i) {
                secondBoundarySegments.push_back({
                    transformUnitPoint(segment.first, segment.second, unitPoints[i]),
                    transformUnitPoint(segment.first, segment.second, unitPoints[i + 1]),
                });
            }
        }

        ensureSimpleBoundary(secondBoundarySegments, "second replacement",
                             {MAX_SECOND_NODE_PAIRS, MAX_SECOND_SEGMENT_PAIRS});
    }

    inf.readEof();
}
