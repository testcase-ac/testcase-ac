#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Rational {
    long long numerator;
    long long denominator;
};

struct Segment {
    int x;
    int y;
    int u;
    int v;
};

struct Interval {
    Rational left;
    Rational right;
};

static bool lessThan(const Rational& a, const Rational& b) {
    return static_cast<__int128>(a.numerator) * b.denominator <
           static_cast<__int128>(b.numerator) * a.denominator;
}

static bool equalTo(const Rational& a, const Rational& b) {
    return static_cast<__int128>(a.numerator) * b.denominator ==
           static_cast<__int128>(b.numerator) * a.denominator;
}

static Rational shadowPoint(int x, int y, int xL, int yL) {
    return Rational{
        static_cast<long long>(yL) * x - static_cast<long long>(y) * xL,
        yL - y,
    };
}

static Interval shadowInterval(const Segment& segment, int xL, int yL) {
    Rational first = shadowPoint(segment.x, segment.y, xL, yL);
    Rational second = shadowPoint(segment.u, segment.v, xL, yL);
    if (lessThan(second, first)) {
        swap(first, second);
    }
    return {first, second};
}

static bool touchesExistingShadow(const vector<Interval>& shadows, const Interval& candidate) {
    for (const Interval& shadow : shadows) {
        if (equalTo(shadow.right, candidate.left) || equalTo(candidate.right, shadow.left)) {
            return true;
        }
    }
    return false;
}

static bool addRandomSegment(vector<Segment>& segments,
                             vector<Interval>& shadows,
                             set<pair<int, int>>& endpoints,
                             int xL,
                             int yL,
                             int coordinateLimit) {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        Segment candidate{
            rnd.next(-coordinateLimit, coordinateLimit),
            rnd.next(1, yL - 1),
            rnd.next(-coordinateLimit, coordinateLimit),
            rnd.next(1, yL - 1),
        };

        pair<int, int> firstEndpoint = {candidate.x, candidate.y};
        pair<int, int> secondEndpoint = {candidate.u, candidate.v};
        if (firstEndpoint == secondEndpoint || endpoints.count(firstEndpoint) ||
            endpoints.count(secondEndpoint)) {
            continue;
        }

        Interval shadow = shadowInterval(candidate, xL, yL);
        if (equalTo(shadow.left, shadow.right) || touchesExistingShadow(shadows, shadow)) {
            continue;
        }

        endpoints.insert(firstEndpoint);
        endpoints.insert(secondEndpoint);
        shadows.push_back(shadow);
        segments.push_back(candidate);
        return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCount = rnd.next(3, 7);
    println(testCount);

    for (int tc = 0; tc < testCount; ++tc) {
        bool emptyCase = rnd.next(10) == 0;
        int n = emptyCase ? 0 : rnd.next(1, 8);
        int yL = emptyCase ? rnd.next(1, 6) : rnd.next(2, 35);
        int xL = rnd.next(-20, 20);
        int coordinateLimit = rnd.any(vector<int>{5, 10, 20, 100});

        vector<Segment> segments;
        vector<Interval> shadows;
        set<pair<int, int>> endpoints;

        for (int i = 0; i < n; ++i) {
            if (!addRandomSegment(segments, shadows, endpoints, xL, yL, coordinateLimit)) {
                n = static_cast<int>(segments.size());
                break;
            }
        }

        println(n);
        println(xL, yL);
        for (const Segment& segment : segments) {
            println(segment.x, segment.y, segment.u, segment.v);
        }
    }

    return 0;
}
