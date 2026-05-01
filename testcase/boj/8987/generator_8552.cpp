#include "testlib.h"
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<long long,long long>> pts;
    int type = rnd.next(0, 4); // 0: rectangle, 1-4: various bottoms

    if (type == 0) {
        // Simple rectangle: N = 4
        long long depth = rnd.next(1, 20);
        long long width = rnd.next(3, 20);

        pts.push_back({0, 0});
        pts.push_back({0, depth});
        pts.push_back({width, depth});
        pts.push_back({width, 0});
    } else {
        // General complex bottom
        int H;
        if (rnd.next(0, 1) == 0)
            H = rnd.next(2, 6);   // small
        else
            H = rnd.next(7, 13);  // medium

        long long Ymax = rnd.next(5, 25);

        vector<long long> y(H + 1);
        vector<long long> dx(H + 1);

        if (type == 1) {
            // Random walk of depths
            y[1] = rnd.next(1LL, Ymax);
            for (int i = 2; i <= H; i++) {
                int step = rnd.next(-2, 2);
                if (step == 0) step = (rnd.next(0, 1) ? 1 : -1);
                long long cand = y[i - 1] + step;
                if (cand < 1) cand = 1;
                if (cand > Ymax) cand = Ymax;
                y[i] = cand;
            }
        } else if (type == 2) {
            // Central deep pit
            long long shallow = rnd.next(1LL, max(2LL, Ymax / 2));
            long long deep = rnd.next(shallow + 1, Ymax);
            for (int i = 1; i <= H; i++) {
                if (i == 1 || i == H) {
                    y[i] = shallow;
                } else if (i == H / 2 || i == H / 2 + 1) {
                    y[i] = deep;
                } else {
                    y[i] = shallow + rnd.next(0LL, deep - shallow);
                }
            }
        } else if (type == 3) {
            // Strictly increasing staircase
            long long maxStart = max(1LL, Ymax - H);
            long long minVal = rnd.next(1LL, maxStart);
            for (int i = 1; i <= H; i++) {
                y[i] = minVal + (i - 1);
            }
        } else { // type == 4
            // Alternating shallow/deep segments
            long long shallow = rnd.next(1LL, max(1LL, Ymax / 3));
            long long deep = rnd.next(shallow + 1, Ymax);
            long long delta = deep - shallow;
            int slack = (delta >= 2 ? (int)min(delta - 1, 3LL) : 0);
            for (int i = 1; i <= H; i++) {
                if (i % 2 == 1) {
                    if (slack > 0)
                        y[i] = shallow + rnd.next(0, slack);
                    else
                        y[i] = shallow;
                } else {
                    if (slack > 0)
                        y[i] = deep - rnd.next(0, slack);
                    else
                        y[i] = deep;
                }
            }
        }

        // Ensure all depths are positive
        for (int i = 1; i <= H; i++) {
            if (y[i] <= 0) y[i] = 1;
        }

        // Fix to avoid identical consecutive depths (which would create
        // identical consecutive vertices on vertical segments).
        for (int i = 2; i <= H; i++) {
            if (y[i] == y[i - 1]) {
                if (y[i] + 1 <= 1000000000LL) y[i]++;
                else y[i]--;
                if (y[i] <= 0) y[i] = 1;
            }
        }

        // Horizontal lengths
        long long totalX = 0;
        for (int i = 1; i <= H; i++) {
            dx[i] = rnd.next(1, 10);
            totalX += dx[i];
        }

        long long x = 0;
        pts.push_back({0, 0});
        for (int i = 1; i <= H; i++) {
            long long vy = y[i];
            // vertical segment (x, previous y) -> (x, vy)
            pts.push_back({x, vy});
            x += dx[i];
            // horizontal segment (x - dx[i], vy) -> (x, vy)
            pts.push_back({x, vy});
        }
        // final vertical up to surface
        pts.push_back({x, 0});
    }

    int N = (int)pts.size();
    int maxK = N / 2;

    int mode = rnd.next(0, 99);
    int K;
    if (mode < 30) {
        K = 1;
    } else if (mode < 60) {
        K = rnd.next(1, min(maxK, 10));
    } else if (mode < 80) {
        K = maxK;
    } else {
        K = rnd.next(1, maxK);
    }

    println(N);
    for (auto &p : pts)
        println(p.first, p.second);
    println(K);

    return 0;
}
