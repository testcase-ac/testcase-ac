#include "testlib.h"
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

pair<int,int> randomSpiralPoint() {
    // Generate a simple strictly increasing length sequence and pick a point on it
    int segments = rnd.next(4, 10);
    int startLen = rnd.next(1, 7);
    vector<int> len(segments);
    len[0] = startLen;
    for (int i = 1; i < segments; ++i) {
        len[i] = len[i - 1] + rnd.next(1, 4);
    }

    int x = 0, y = 0;
    int dir = 0; // 0:R,1:U,2:L,3:D
    vector<pair<int,int>> cand;

    for (int i = 0; i < segments; ++i) {
        int L = len[i];
        int nx = x, ny = y;
        if (dir == 0) nx += L;
        else if (dir == 1) ny += L;
        else if (dir == 2) nx -= L;
        else ny -= L;

        if (dir == 0 || dir == 2) {
            int from = min(x, nx) + 1;
            int to = max(x, nx);
            for (int tx = from; tx <= to; ++tx) {
                if (tx > 0 && y > 0 && tx <= 10000 && y <= 10000)
                    cand.emplace_back(tx, y);
            }
        } else {
            int from = min(y, ny) + 1;
            int to = max(y, ny);
            for (int ty = from; ty <= to; ++ty) {
                if (x > 0 && ty > 0 && x <= 10000 && ty <= 10000)
                    cand.emplace_back(x, ty);
            }
        }

        x = nx;
        y = ny;
        dir = (dir + 1) % 4;
    }

    if (!cand.empty())
        return rnd.any(cand);

    // Fallback: small random point
    return {rnd.next(1, 20), rnd.next(1, 20)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MIN_P = 6;
    const int MAX_P = 14;
    int P = rnd.next(MIN_P, MAX_P);

    println(P);

    vector<pair<int,int>> preset = {
        {1, 1},
        {2, 1},
        {1, 2},
        {2, 2},
        {10000, 1},
        {1, 10000}
    };

    for (int t = 1; t <= P; ++t) {
        int x, y;
        if (t <= (int)preset.size()) {
            x = preset[t - 1].first;
            y = preset[t - 1].second;
        } else {
            int type = rnd.next(0, 5);
            if (type == 0) {
                // Small random
                x = rnd.next(1, 10);
                y = rnd.next(1, 10);
            } else if (type == 1) {
                // Medium random
                x = rnd.next(1, 100);
                y = rnd.next(1, 100);
            } else if (type == 2) {
                // Large random
                x = rnd.next(1, 10000);
                y = rnd.next(1, 10000);
            } else if (type == 3) {
                // Near diagonal
                int base = rnd.next(1, 10000);
                int delta = rnd.next(-3, 3);
                x = base;
                y = base + delta;
                if (y < 1) y = 1;
                if (y > 10000) y = 10000;
            } else if (type == 4) {
                // Near axes inside first quadrant
                if (rnd.next(0, 1) == 0) {
                    x = rnd.next(1, 10000);
                    y = rnd.next(1, 3);
                } else {
                    x = rnd.next(1, 3);
                    y = rnd.next(1, 10000);
                }
            } else {
                // Guaranteed reachable from a constructed spiral
                pair<int,int> p = randomSpiralPoint();
                x = p.first;
                y = p.second;
            }
        }

        println(t, x, y);
    }

    return 0;
}
