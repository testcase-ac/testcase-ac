#include "testlib.h"
using namespace std;

vector<pair<int,int>> genScenario(int id) {
    vector<pair<int,int>> pts;
    if (id == 0) {
        // Small triangle-like path
        int n = 3;
        pts.resize(n);
        int x0 = 0;
        int y0 = rnd.next(-5, 5);
        int x1 = x0 + rnd.next(1, 5);
        int y1 = rnd.next(-5, 5);
        int x2 = x1 + rnd.next(1, 5);
        int y2 = rnd.next(-5, 5);
        pts[0] = {x0, y0};
        pts[1] = {x1, y1};
        pts[2] = {x2, y2};
    } else if (id == 1) {
        // Moderately smooth random path
        int n = rnd.next(4, 10);
        pts.resize(n);
        vector<int> xs(n), ys(n);
        xs[0] = 0;
        ys[0] = rnd.next(-5, 5);
        for (int i = 1; i < n; i++) {
            xs[i] = xs[i-1] + rnd.next(1, 3); // strictly increasing x
            int step = rnd.next(-3, 3);
            ys[i] = ys[i-1] + step;
        }
        for (int i = 0; i < n; i++) pts[i] = {xs[i], ys[i]};
    } else if (id == 2) {
        // Zigzag up and down with relatively large amplitude
        int n = rnd.next(6, 12);
        pts.resize(n);
        int baseY = rnd.next(-3, 3);
        int A = rnd.next(2, 8);
        int x = 0;
        for (int i = 0; i < n; i++) {
            x += 1;
            int noise = rnd.next(-1, 1);
            int y = (i % 2 == 0 ? baseY + A : baseY - A) + noise;
            pts[i] = {x, y};
        }
    } else if (id == 3) {
        // Mostly flat with occasional spikes
        int n = rnd.next(6, 15);
        pts.resize(n);
        int baseY = rnd.next(-3, 3);
        int x = 0;
        for (int i = 0; i < n; i++) {
            x += rnd.next(1, 2);
            int y;
            if (rnd.next(0, 99) < 70) {
                y = baseY;
            } else {
                int sign = rnd.next(0, 1) ? 1 : -1;
                y = baseY + sign * rnd.next(1, 7);
            }
            pts[i] = {x, y};
        }
    } else if (id == 4) {
        // Steep slopes, large vertical variation
        int n = rnd.next(4, 10);
        pts.resize(n);
        vector<int> xs(n), ys(n);
        xs[0] = 0;
        ys[0] = rnd.next(-5, 5);
        for (int i = 1; i < n; i++) {
            xs[i] = xs[i-1] + rnd.next(2, 5);
            int sign = rnd.next(0, 1) ? 1 : -1;
            int mag = rnd.next(3, 8);
            ys[i] = ys[i-1] + sign * mag;
        }
        for (int i = 0; i < n; i++) pts[i] = {xs[i], ys[i]};
    } else if (id == 5) {
        // U-shaped / valley-like path to encourage useful bridges
        int n = 5;
        pts.resize(n);
        int H = rnd.next(5, 15);
        int extra = rnd.next(0, 5);
        int x = 0;
        int dx1 = rnd.next(1, 3);
        int dx2 = rnd.next(1, 3);
        int dx3 = rnd.next(1, 3);
        int dx4 = rnd.next(1, 3);
        int y0 = H;
        int y1 = rnd.next(-2, 2);
        int y2 = -H - extra;
        int y3 = rnd.next(-2, 2);
        int y4 = H;
        pts[0] = {x, y0};
        x += dx1;
        pts[1] = {x, y1};
        x += dx2;
        pts[2] = {x, y2};
        x += dx3;
        pts[3] = {x, y3};
        x += dx4;
        pts[4] = {x, y4};
    } else if (id == 6) {
        // Monotone in y (always increasing or decreasing)
        int n = rnd.next(3, 12);
        pts.resize(n);
        vector<int> xs(n), ys(n);
        xs[0] = 0;
        ys[0] = rnd.next(-5, 5);
        int dir = rnd.next(0, 1) ? 1 : -1; // up or down
        for (int i = 1; i < n; i++) {
            xs[i] = xs[i-1] + rnd.next(1, 3);
            int step = rnd.next(0, 3);
            ys[i] = ys[i-1] + dir * step;
        }
        for (int i = 0; i < n; i++) pts[i] = {xs[i], ys[i]};
    } else { // id == 7
        // Manhattan staircase: x and y both nondecreasing, with vertical segments
        int n = rnd.next(3, 12);
        int x = 0, y = 0;
        pts.emplace_back(x, y);
        bool hadHoriz = false;
        for (int i = 1; i < n; i++) {
            bool doHoriz;
            if (i == n - 1 && !hadHoriz) {
                doHoriz = true; // ensure at least one horizontal step
            } else {
                doHoriz = (rnd.next(0, 1) == 0);
            }
            if (doHoriz) {
                int dx = rnd.next(1, 5);
                x += dx;
                hadHoriz = true;
            } else {
                int dy = rnd.next(1, 5);
                y += dy;
            }
            pts.emplace_back(x, y);
        }
    }

    // Apply random shift to coordinates to diversify
    int shiftX = rnd.next(-20, 20);
    int shiftY = rnd.next(-20, 20);
    for (auto &p : pts) {
        p.first += shiftX;
        p.second += shiftY;
    }

    return pts;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 7);
    vector<pair<int,int>> pts = genScenario(scenario);
    int n = (int)pts.size();

    println(n);
    for (auto &p : pts) {
        println(p.first, p.second);
    }

    return 0;
}
