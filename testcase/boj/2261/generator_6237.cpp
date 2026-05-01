#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of points
    int n = rnd.next(2, 80);
    vector<pair<int,int>> pts;
    // choose distribution type: 0=uniform,1=cluster,2=grid
    int distType = rnd.next(0, 2);
    if (distType == 0) {
        // uniform random points
        for (int i = 0; i < n; i++) {
            int x = rnd.next(-10000, 10000);
            int y = rnd.next(-10000, 10000);
            pts.emplace_back(x, y);
        }
    } else if (distType == 1) {
        // clusters
        int maxC = min(5, n);
        int c = rnd.next(1, maxC);
        vector<pair<int,int>> centers;
        for (int i = 0; i < c; i++) {
            int cx = rnd.next(-9000, 9000);
            int cy = rnd.next(-9000, 9000);
            centers.emplace_back(cx, cy);
        }
        for (int i = 0; i < n; i++) {
            auto cen = centers[rnd.next(0, c-1)];
            int dx = rnd.next(-100, 100);
            int dy = rnd.next(-100, 100);
            int x = cen.first + dx;
            int y = cen.second + dy;
            if (x < -10000) x = -10000;
            if (x > 10000) x = 10000;
            if (y < -10000) y = -10000;
            if (y > 10000) y = 10000;
            pts.emplace_back(x, y);
        }
    } else {
        // grid with jitter
        int g = rnd.next(2, min(n, 10));
        int rows = (n + g - 1) / g;
        int dx = (g > 1 ? 20000 / (g - 1) : 0);
        int dy = (rows > 1 ? 20000 / (rows - 1) : 0);
        int jx = max(1, dx / 4);
        int jy = max(1, dy / 4);
        for (int i = 0; i < rows && (int)pts.size() < n; i++) {
            for (int j = 0; j < g && (int)pts.size() < n; j++) {
                int x = -10000 + dx * j + rnd.next(-jx, jx);
                int y;
                if (rows > 1)
                    y = -10000 + dy * i + rnd.next(-jy, jy);
                else
                    y = rnd.next(-10000, 10000);
                if (x < -10000) x = -10000;
                if (x > 10000) x = 10000;
                if (y < -10000) y = -10000;
                if (y > 10000) y = 10000;
                pts.emplace_back(x, y);
            }
        }
    }
    // introduce some duplicates randomly
    int maxDup = max(1, n / 5);
    int dupCount = rnd.wnext(maxDup + 1, -1);
    for (int i = 0; i < dupCount; i++) {
        int to = rnd.next(0, n-1);
        int from = rnd.next(0, n-1);
        pts[to] = pts[from];
    }
    // shuffle the points to avoid any order bias
    shuffle(pts.begin(), pts.end());
    // output
    println(n);
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}
