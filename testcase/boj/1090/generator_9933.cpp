#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int,int>> pts;

    int type = rnd.next(0, 7);

    if (type == 0) {
        // All checkers on the same cell (many duplicates)
        int N = rnd.next(1, 15);
        int x = rnd.next(1, 30);
        int y = rnd.next(1, 30);
        for (int i = 0; i < N; ++i)
            pts.push_back({x, y});
    } else if (type == 1) {
        // Horizontal line
        int N = rnd.next(2, 15);
        int y = rnd.next(1, 30);
        int x = rnd.next(1, 30);
        pts.push_back({x, y});
        for (int i = 1; i < N; ++i) {
            int mode = rnd.next(0, 2);
            int step;
            if (mode == 0) step = rnd.next(0, 1);
            else if (mode == 1) step = rnd.next(0, 3);
            else {
                int choices[4] = {0, 10, 50, 200};
                step = choices[rnd.next(0, 3)];
            }
            x += step;
            if (x > 1000000) x = 1000000; // just in case
            pts.push_back({x, y});
        }
    } else if (type == 2) {
        // Vertical line
        int N = rnd.next(2, 15);
        int x = rnd.next(1, 30);
        int y = rnd.next(1, 30);
        pts.push_back({x, y});
        for (int i = 1; i < N; ++i) {
            int mode = rnd.next(0, 2);
            int step;
            if (mode == 0) step = rnd.next(0, 1);
            else if (mode == 1) step = rnd.next(0, 3);
            else {
                int choices[4] = {0, 10, 50, 200};
                step = choices[rnd.next(0, 3)];
            }
            y += step;
            if (y > 1000000) y = 1000000;
            pts.push_back({x, y});
        }
    } else if (type == 3) {
        // Diagonal-ish pattern
        int N = rnd.next(3, 15);
        int x0 = rnd.next(1, 30);
        int y0 = rnd.next(1, 30);
        bool mainDiag = rnd.next(0, 1); // main or anti-diagonal
        for (int i = 0; i < N; ++i) {
            int x = x0 + i;
            int y;
            if (mainDiag) y = y0 + i;
            else y = y0 - i;
            if (y < 1) y = 1 + (i % 5); // keep inside bounds, slight distortion
            pts.push_back({x, y});
        }
    } else if (type == 4) {
        // Small dense cluster around a center
        int N = rnd.next(5, 15);
        int cx = rnd.next(5, 30);
        int cy = rnd.next(5, 30);
        for (int i = 0; i < N; ++i) {
            int x = cx + rnd.next(-2, 2);
            int y = cy + rnd.next(-2, 2);
            if (x < 1) x = 1;
            if (y < 1) y = 1;
            pts.push_back({x, y});
        }
    } else if (type == 5) {
        // Two clusters far apart
        int N = rnd.next(6, 15);
        int N1 = rnd.next(1, N - 1);
        int N2 = N - N1;

        int ax = rnd.next(5, 30);
        int ay = rnd.next(5, 30);
        int bx = rnd.next(200, 400);   // far from A
        int by = rnd.next(200, 400);

        for (int i = 0; i < N1; ++i) {
            int x = ax + rnd.next(-1, 1);
            int y = ay + rnd.next(-1, 1);
            if (x < 1) x = 1;
            if (y < 1) y = 1;
            pts.push_back({x, y});
        }
        for (int i = 0; i < N2; ++i) {
            int x = bx + rnd.next(-1, 1);
            int y = by + rnd.next(-1, 1);
            if (x < 1) x = 1;
            if (y < 1) y = 1;
            if (x > 1000000) x = 1000000;
            if (y > 1000000) y = 1000000;
            pts.push_back({x, y});
        }
    } else if (type == 6) {
        // Random medium coordinates in a small board
        int N = rnd.next(3, 15);
        for (int i = 0; i < N; ++i) {
            int x = rnd.next(1, 50);
            int y = rnd.next(1, 50);
            pts.push_back({x, y});
        }
    } else if (type == 7) {
        // Random large coordinates, near extremes
        int N = rnd.next(2, 10);
        for (int i = 0; i < N; ++i) {
            int pattern = rnd.next(0, 2);
            int x, y;
            if (pattern == 0) {
                // completely random large
                x = rnd.next(1, 1000000);
                y = rnd.next(1, 1000000);
            } else if (pattern == 1) {
                // near (1,1)
                x = rnd.next(1, 20);
                y = rnd.next(1, 20);
            } else {
                // near (1e6, 1e6)
                x = 1000000 - rnd.next(0, 20);
                y = 1000000 - rnd.next(0, 20);
            }
            pts.push_back({x, y});
        }
    }

    // Shuffle order of checkers for randomness
    shuffle(pts.begin(), pts.end());

    int N = (int)pts.size();
    println(N);
    for (auto &p : pts)
        println(p.first, p.second);

    return 0;
}
