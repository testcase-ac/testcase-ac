#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of animals
    int n = rnd.next(1, 10);

    // Hyper-parameter: coordinate range
    vector<int> coordMaxList = {5, 10, 100, 1000, 1000000};
    int coordMax = rnd.any(coordMaxList);

    // Decide cluster or scattered
    bool clusterMode = rnd.next() < 0.5;
    set<pair<int,int>> used;
    vector<pair<int,int>> pts;

    if (clusterMode) {
        // pick a cluster center
        int cx = rnd.next(0, min(coordMax, 100));
        int cy = rnd.next(0, min(coordMax, 100));
        int clusterCount = rnd.next(1, n);
        for (int i = 0; i < clusterCount; ) {
            int dx = rnd.next(-5, 5);
            int dy = rnd.next(-5, 5);
            int x = cx + dx;
            int y = cy + dy;
            x = max(0, min(coordMax, x));
            y = max(0, min(coordMax, y));
            if (x == 0 && y == 0) continue;
            if (used.insert({x, y}).second) {
                pts.emplace_back(x, y);
                ++i;
            }
        }
        // fill the rest scattered
        while ((int)pts.size() < n) {
            int x = rnd.next(0, coordMax);
            int y = rnd.next(0, coordMax);
            if ((x == 0 && y == 0) || !used.insert({x,y}).second) continue;
            pts.emplace_back(x, y);
        }
    } else {
        // fully scattered
        while ((int)pts.size() < n) {
            int x = rnd.next(0, coordMax);
            int y = rnd.next(0, coordMax);
            if ((x == 0 && y == 0) || !used.insert({x,y}).second) continue;
            pts.emplace_back(x, y);
        }
    }

    // Hyper-parameters for time intervals
    vector<int> timeMaxList = {10, 100, 1000, 1000000000};
    int timeMax = rnd.any(timeMaxList);
    vector<int> lenMaxList = {1, 5, 10, 100, 1000};
    int lenMax = rnd.any(lenMaxList);

    vector<pair<int,int>> times;
    for (int i = 0; i < n; ++i) {
        int v = rnd.next(0, max(1, timeMax - 1));
        int len = rnd.next(1, lenMax);
        long long w = (long long)v + len;
        if (w > timeMax) w = timeMax;
        if (w <= v) w = (long long)v + 1;
        times.emplace_back(v, (int)w);
    }

    // Combine and shuffle
    struct Animal { int x, y, v, w; };
    vector<Animal> A(n);
    for (int i = 0; i < n; ++i) {
        A[i] = {pts[i].first, pts[i].second, times[i].first, times[i].second};
    }
    shuffle(A.begin(), A.end());

    // Output
    println(n);
    for (auto &a : A) println(a.x, a.y);
    for (auto &a : A) println(a.v, a.w);

    return 0;
}
