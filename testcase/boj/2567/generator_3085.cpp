#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of papers
    int N = rnd.next(1, 10);
    int mode = rnd.next(0, 2); // 0 = random, 1 = cluster, 2 = line
    vector<pair<int,int>> coords;

    if (mode == 0) {
        // Uniform random distinct positions
        set<pair<int,int>> seen;
        while ((int)coords.size() < N) {
            int x = rnd.next(1, 90);
            int y = rnd.next(1, 90);
            if (seen.insert({x, y}).second) {
                coords.emplace_back(x, y);
            }
        }
    } else if (mode == 1) {
        // Cluster around a center
        int cx = rnd.next(1, 90);
        int cy = rnd.next(1, 90);
        int lx, hx, ly, hy, R;
        // ensure enough room to place N distinct
        do {
            R = rnd.next(1, 20);
            lx = max(1, cx - R);
            hx = min(90, cx + R);
            ly = max(1, cy - R);
            hy = min(90, cy + R);
        } while ((hx - lx + 1) * (hy - ly + 1) < N);
        set<pair<int,int>> seen;
        while ((int)coords.size() < N) {
            int x = rnd.next(lx, hx);
            int y = rnd.next(ly, hy);
            if (seen.insert({x, y}).second) {
                coords.emplace_back(x, y);
            }
        }
    } else {
        // Line of papers (touching or spaced)
        bool horizontal = rnd.next(0, 1) == 0;
        int step;
        if (N == 1) {
            step = rnd.next(1, 10);
        } else {
            // ensure last coord <= 90
            do {
                step = rnd.next(1, 10);
            } while ((long long)step * (N - 1) > 89);
        }
        int span = step * (N - 1);
        if (horizontal) {
            int y = rnd.next(1, 90);
            int maxStart = 90 - span;
            int x0 = rnd.next(1, maxStart);
            for (int i = 0; i < N; i++) {
                coords.emplace_back(x0 + i * step, y);
            }
        } else {
            int x = rnd.next(1, 90);
            int maxStart = 90 - span;
            int y0 = rnd.next(1, maxStart);
            for (int i = 0; i < N; i++) {
                coords.emplace_back(x, y0 + i * step);
            }
        }
    }

    // Randomize order
    shuffle(coords.begin(), coords.end());
    // Output
    println(N);
    for (auto &p : coords) {
        println(p.first, p.second);
    }
    return 0;
}
