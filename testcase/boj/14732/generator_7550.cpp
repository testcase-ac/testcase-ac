#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: maximum N
    vector<int> Ncaps = {5, 10, 15, 20};
    int Ncap = rnd.any(Ncaps);
    int N = rnd.next(2, Ncap);

    // Hyper-parameter: coordinate max
    vector<int> Ccaps = {10, 50, 100, 500};
    int Cmax = rnd.any(Ccaps);

    // Decide whether to include one big covering rectangle (~25% chance)
    bool doBig = rnd.next(0, 3) == 0;

    vector<array<int,4>> rects;
    if (doBig) {
        rects.push_back({0, 0, Cmax, Cmax});
    }

    while ((int)rects.size() < N) {
        int x1, y1, x2, y2;
        bool made = false;

        // ~25% chance to nest inside an existing rectangle with room
        if (!made && rnd.next(0, 3) == 0) {
            vector<int> candidates;
            for (int i = 0; i < (int)rects.size(); i++) {
                auto &r = rects[i];
                if (r[2] - r[0] >= 2 && r[3] - r[1] >= 2)
                    candidates.push_back(i);
            }
            if (!candidates.empty()) {
                auto &p = rects[rnd.any(candidates)];
                // choose nested within p
                x1 = rnd.next(p[0], p[2] - 1);
                x2 = rnd.next(x1 + 1, p[2]);
                y1 = rnd.next(p[1], p[3] - 1);
                y2 = rnd.next(y1 + 1, p[3]);
                made = true;
            }
        }

        // Otherwise random rectangle
        if (!made) {
            int t = rnd.next(0, 2);
            if (t == 0) {
                // small 1x1
                x1 = rnd.next(0, Cmax - 1);
                y1 = rnd.next(0, Cmax - 1);
                x2 = x1 + 1;
                y2 = y1 + 1;
            } else if (t == 1) {
                // skinny (height=1)
                int w = rnd.next(1, max(1, Cmax / 2));
                x1 = rnd.next(0, Cmax - w);
                x2 = x1 + w;
                y1 = rnd.next(0, Cmax - 1);
                y2 = y1 + 1;
            } else {
                // general
                int w = rnd.next(1, max(1, Cmax / 2));
                int h = rnd.next(1, max(1, Cmax / 2));
                x1 = rnd.next(0, Cmax - w);
                x2 = x1 + w;
                y1 = rnd.next(0, Cmax - h);
                y2 = y1 + h;
            }
        }

        rects.push_back({x1, y1, x2, y2});
    }

    // Shuffle to avoid ordering hints
    shuffle(rects.begin(), rects.end());

    // Output
    println(N);
    for (auto &r : rects) {
        println(r[0], r[1], r[2], r[3]);
    }

    return 0;
}
