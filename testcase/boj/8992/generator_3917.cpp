#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);

    const int XMAX = 200;
    const int YMAX = 200;
    vector<int> weightTypes = {-1, 0, 1};

    for (int tc = 0; tc < T; tc++) {
        // sizes
        int n = rnd.next(1, 10);
        int m = rnd.next(1, 10);
        println(n, m);

        // 1) Generate horizontal segments
        // pick distinct y-coordinates for horizontals
        vector<int> allY(YMAX);
        for (int i = 0; i < YMAX; i++) allY[i] = i + 1;
        shuffle(allY.begin(), allY.end());
        vector<int> hY(allY.begin(), allY.begin() + n);

        // store endpoints to forbid for verticals
        vector<bool> forbidX(XMAX+1, false), forbidY(YMAX+1, false);

        // choose a weight-bias type
        int wt = rnd.any(weightTypes);

        struct HSeg { int x1, y, x2, w; };
        vector<HSeg> H;
        for (int i = 0; i < n; i++) {
            int y = hY[i];
            forbidY[y] = true;
            // choose x1 < x2
            int x1 = rnd.next(1, XMAX-1);
            int x2 = rnd.next(x1 + 1, XMAX);
            forbidX[x1] = true;
            forbidX[x2] = true;
            int w = rnd.wnext(20, wt) + 1;
            H.push_back({x1, y, x2, w});
        }

        // print horizontals
        for (auto &hg : H) {
            println(hg.x1, hg.y, hg.x2, hg.y, hg.w);
        }

        // 2) Generate vertical segments
        // prepare candidate x's excluding horizontal endpoints
        vector<int> candX;
        for (int x = 1; x <= XMAX; x++) {
            if (!forbidX[x]) candX.push_back(x);
        }
        shuffle(candX.begin(), candX.end());
        candX.resize(m); // take m distinct x's

        // prepare candidate y's excluding horizontal y's
        vector<int> candY;
        for (int y = 1; y <= YMAX; y++) {
            if (!forbidY[y]) candY.push_back(y);
        }

        for (int i = 0; i < m; i++) {
            int vx = candX[i];
            // pick two distinct y1,y2 from candY
            int y1, y2;
            if ((int)candY.size() >= 2) {
                int i1 = rnd.next(0, (int)candY.size() - 1);
                int i2 = rnd.next(0, (int)candY.size() - 1);
                while (i2 == i1)
                    i2 = rnd.next(0, (int)candY.size() - 1);
                y1 = candY[i1];
                y2 = candY[i2];
                if (y1 > y2) swap(y1, y2);
            } else {
                // fallback (should not happen for small n)
                y1 = 1;
                y2 = YMAX;
            }
            int w = rnd.wnext(20, wt) + 1;
            println(vx, y1, vx, y2, w);
        }
    }
    return 0;
}
