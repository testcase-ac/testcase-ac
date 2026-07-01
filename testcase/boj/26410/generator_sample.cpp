#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
};

long long cross(const Point& a, const Point& b, const Point& c) {
    long long ux = b.x - a.x;
    long long uy = b.y - a.y;
    long long vx = c.x - a.x;
    long long vy = c.y - a.y;
    return ux * vy - uy * vx;
}

vector<int> chooseDistinct(int count, int lo, int hi) {
    vector<int> values;
    for (int x = lo; x <= hi; ++x) {
        values.push_back(x);
    }
    shuffle(values.begin(), values.end());
    values.resize(count);
    sort(values.begin(), values.end());
    return values;
}

bool hasThreeConsecutiveCollinear(const vector<Point>& p) {
    int n = int(p.size());
    for (int i = 0; i < n; ++i) {
        if (cross(p[i], p[(i + 1) % n], p[(i + 2) % n]) == 0) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Point> p;
    for (int attempt = 0; attempt < 1000; ++attempt) {
        int n = rnd.next(3, 12);
        int width = rnd.next(max(3, n), 35);
        int height = rnd.next(max(3, n), 35);

        p.clear();
        p.push_back({0, 0});
        p.push_back({width, 0});

        int middleCount = n - 3;
        vector<int> xs = chooseDistinct(middleCount, 1, width - 1);
        vector<int> ys = chooseDistinct(middleCount, 1, height - 1);
        reverse(xs.begin(), xs.end());

        for (int i = 0; i < middleCount; ++i) {
            p.push_back({xs[i], ys[i]});
        }
        p.push_back({0, height});

        if (!hasThreeConsecutiveCollinear(p)) {
            break;
        }
    }

    println(int(p.size()));
    for (const Point& point : p) {
        println(point.x, point.y);
    }

    return 0;
}
