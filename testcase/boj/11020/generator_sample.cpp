#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const long double PI = acosl(-1.0L);
const long double TWO_PI = 2.0L * PI;

struct Point {
    long double alpha;
    long double radius;
};

string decimalToken(long double value) {
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%.6Lf", value);
    return string(buffer);
}

void addUnique(vector<Point>& points, set<pair<string, string>>& used,
               long double alpha, long double radius) {
    while (alpha < 0.0L) {
        alpha += TWO_PI;
    }
    while (alpha >= TWO_PI) {
        alpha -= TWO_PI;
    }

    for (int attempt = 0; attempt < 100; ++attempt) {
        string alphaToken = decimalToken(alpha);
        string radiusToken = decimalToken(radius);
        if (used.insert({alphaToken, radiusToken}).second) {
            points.push_back({alpha, radius});
            return;
        }

        radius += 0.000001L;
        if (radius > 1.0L) {
            radius = 0.000001L;
            alpha += 0.000001L;
            if (alpha >= TWO_PI) {
                alpha -= TWO_PI;
            }
        }
    }
}

long double randomAlpha() {
    return rnd.next(0, 6283184) / 1000000.0L;
}

long double randomRadius() {
    return rnd.next(1, 1000000) / 1000000.0L;
}

vector<Point> makeCase(int mode, int n) {
    vector<Point> points;
    set<pair<string, string>> used;

    if (mode == 0) {
        int slices = rnd.any(vector<int>{2, 3, 4, 5, 6, 8, 10});
        int perSlice = max(1, n / slices);
        n = slices * perSlice;
        long double offset = randomAlpha() / slices;
        for (int i = 0; i < slices; ++i) {
            for (int j = 0; j < perSlice; ++j) {
                long double alpha = offset + i * TWO_PI / slices + j * 0.000007L;
                long double radius = (j + 1.0L) / (perSlice + 1.0L);
                addUnique(points, used, alpha, radius);
            }
        }
    } else if (mode == 1) {
        long double base = randomAlpha();
        for (int i = 0; i < n; ++i) {
            addUnique(points, used, base, (i + 1.0L) / (n + 1.0L));
        }
    } else if (mode == 2) {
        long double edge = rnd.any(vector<long double>{0.0L, PI / 2.0L, PI, 3.0L * PI / 2.0L});
        for (int i = 0; i < n; ++i) {
            long double delta = (i % 2 == 0 ? 1 : -1) * (i + 1) * 0.000011L;
            addUnique(points, used, edge + delta, randomRadius());
        }
    } else {
        while ((int)points.size() < n) {
            addUnique(points, used, randomAlpha(), randomRadius());
        }
    }

    shuffle(points.begin(), points.end());
    return points;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int k = rnd.next(2, 6);
    vector<vector<Point>> cases;
    int remaining = 200;

    for (int tc = 0; tc < k; ++tc) {
        int maxN = min(remaining - (k - tc - 1), 40);
        int n = rnd.next(1, maxN);
        int mode = tc < 4 ? tc : rnd.next(0, 3);
        vector<Point> points = makeCase(mode, n);
        remaining -= (int)points.size();
        cases.push_back(points);
    }

    println((int)cases.size());
    for (const vector<Point>& points : cases) {
        println((int)points.size());
        for (const Point& point : points) {
            printf("%s %s\n",
                   decimalToken(point.alpha).c_str(),
                   decimalToken(point.radius).c_str());
        }
    }

    return 0;
}
