#include "testlib.h"

#include <set>
#include <utility>
#include <vector>
using namespace std;

using Point = pair<long long, long long>;

const long long kMaxCoord = 1000000000LL;

void addPoint(set<Point>& used, vector<Point>& points, long long x, long long y) {
    x = max(0LL, min(kMaxCoord, x));
    y = max(0LL, min(kMaxCoord, y));
    if (used.insert({x, y}).second) {
        points.push_back({x, y});
    }
}

void addRandomPoint(set<Point>& used, vector<Point>& points) {
    while (true) {
        long long x = rnd.next(0LL, kMaxCoord);
        long long y = rnd.next(0LL, kMaxCoord);
        if (used.insert({x, y}).second) {
            points.push_back({x, y});
            return;
        }
    }
}

void takeRandomCandidates(vector<Point> candidates, vector<Point>& points, int count) {
    shuffle(candidates.begin(), candidates.end());
    points.insert(points.end(), candidates.begin(), candidates.begin() + count);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 24);
    int targetM = rnd.next(1, 45);

    set<Point> used;
    vector<Point> points;

    if (mode == 0) {
        long long baseX = rnd.next(0LL, kMaxCoord - 30);
        long long baseY = rnd.next(0LL, kMaxCoord - 30);
        int width = rnd.next(1, 8);
        int height = rnd.next(1, 8);
        targetM = rnd.next(1, min(45, width * height));
        vector<Point> candidates;
        for (int dx = 0; dx < width; ++dx)
            for (int dy = 0; dy < height; ++dy)
                candidates.push_back({baseX + dx, baseY + dy});
        takeRandomCandidates(candidates, points, targetM);
    } else if (mode == 1) {
        set<long long> usedXs, usedYs;
        vector<long long> xs, ys;
        int xCount = rnd.next(1, 6);
        int yCount = rnd.next(1, 6);
        while ((int)xs.size() < xCount) {
            long long x = rnd.next(0LL, 30LL);
            if (usedXs.insert(x).second) xs.push_back(x);
        }
        while ((int)ys.size() < yCount) {
            long long y = rnd.next(0LL, 30LL);
            if (usedYs.insert(y).second) ys.push_back(y);
        }
        targetM = rnd.next(1, min(45, xCount * yCount));
        vector<Point> candidates;
        for (long long x : xs)
            for (long long y : ys)
                candidates.push_back({x, y});
        takeRandomCandidates(candidates, points, targetM);
    } else if (mode == 2) {
        vector<Point> candidates = {
            {0, 0},
            {0, kMaxCoord},
            {kMaxCoord, 0},
            {kMaxCoord, kMaxCoord},
        };
        for (int i = 0; i < 30; ++i) {
            long long near = rnd.next(0LL, 12LL);
            long long far = kMaxCoord - rnd.next(0LL, 12LL);
            candidates.push_back({near, rnd.next(0LL, 20LL)});
            candidates.push_back({far, kMaxCoord - rnd.next(0LL, 20LL)});
            candidates.push_back({rnd.next(0LL, 20LL), far});
        }
        shuffle(candidates.begin(), candidates.end());
        targetM = rnd.next(1, min(40, (int)candidates.size()));
        for (Point point : candidates) {
            addPoint(used, points, point.first, point.second);
            if ((int)points.size() == targetM) break;
        }
    } else if (mode == 3) {
        long long step = rnd.next(1LL, 100000000LL);
        long long startX = rnd.next(0LL, kMaxCoord - step * 8);
        long long startY = rnd.next(0LL, kMaxCoord - step * 8);
        int maxCount = (int)min((kMaxCoord - max(startX, startY)) / step + 1, 20LL);
        targetM = rnd.next(3, maxCount);
        for (int i = 0; i < targetM; ++i) {
            long long noiseX = rnd.next(0LL, min(3LL, step - 1));
            long long noiseY = rnd.next(0LL, min(3LL, step - 1));
            addPoint(used, points, startX + i * step + noiseX,
                     startY + i * step + noiseY);
        }
    } else if (mode == 4) {
        n = rnd.any(vector<int>{2, 3, 4, 200000});
        targetM = rnd.next(1, 35);
        while ((int)points.size() < targetM) {
            long long x = rnd.next(0LL, 1000LL) * 1000000LL + rnd.next(0LL, 5LL);
            long long y = rnd.next(0LL, 1000LL) * 1000000LL + rnd.next(0LL, 5LL);
            addPoint(used, points, x, y);
        }
    } else {
        targetM = rnd.next(1, 50);
        while ((int)points.size() < targetM) addRandomPoint(used, points);
    }

    shuffle(points.begin(), points.end());
    println(n, (int)points.size());
    for (Point point : points) {
        println(point.first, point.second);
    }

    return 0;
}
