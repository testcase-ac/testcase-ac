#include "testlib.h"
#include <vector>
#include <string>
#include <deque>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = rnd.next(4, 9);
    int M = rnd.next(4, 9);

    int D = rnd.next(2, min(N - 2, M - 2)); // Manhattan distance (moves)
    bool solvable = rnd.next(0, 1);

    int K;
    if (solvable) {
        K = rnd.next(0, 27);
    } else {
        // ensure we can force "first step digit > K" with digits in [0..9]
        K = rnd.next(0, 8);
    }

    // choose |dx| + |dy| = D
    int dxAbs = rnd.next(0, D);
    int dyAbs = D - dxAbs;

    int signX = (dxAbs == 0) ? 0 : (rnd.next(0, 1) ? 1 : -1);
    int signY = (dyAbs == 0) ? 0 : (rnd.next(0, 1) ? 1 : -1);

    // choose S so that H stays in-bounds
    int syMin = 0, syMax = N - 1;
    int sxMin = 0, sxMax = M - 1;

    if (signY == 1) syMax = N - 1 - dyAbs;
    if (signY == -1) syMin = dyAbs;
    if (signX == 1) sxMax = M - 1 - dxAbs;
    if (signX == -1) sxMin = dxAbs;

    int sy = rnd.next(syMin, syMax);
    int sx = rnd.next(sxMin, sxMax);

    int hy = sy + signY * dyAbs;
    int hx = sx + signX * dxAbs;

    // build monotone path steps and shuffle for variety
    vector<pair<int,int>> steps;
    steps.reserve(D);
    for (int i = 0; i < dxAbs; i++) steps.push_back({0, signX});
    for (int i = 0; i < dyAbs; i++) steps.push_back({signY, 0});

    // testlib shuffle (NOT std::shuffle)
    shuffle(steps.begin(), steps.end());

    // materialize path positions: path[0]=S, path[D]=H
    vector<pair<int,int>> path;
    path.reserve(D + 1);
    int y = sy, x = sx;
    path.push_back({y, x});
    for (auto [dy, dx] : steps) {
        y += dy; x += dx;
        path.push_back({y, x});
    }

    // grid init: all walls
    vector<string> grid(N, string(M, 'X'));
    grid[sy][sx] = 'S';
    grid[hy][hx] = 'H';

    // generate digits for intermediate cells path[1..D-1]
    vector<int> digits;
    digits.reserve(D - 1);

    if (solvable) {
        deque<int> last; // previous up to 2 visited cell values
        last.push_back(0); // S has 0

        for (int i = 1; i <= D - 1; i++) {
            int sumPrev = 0;
            for (int v : last) sumPrev += v;

            // need d in [0,9] and d + sumPrev <= K
            int mx = K - sumPrev;
            if (mx > 9) mx = 9;
            if (mx < 0) mx = 0; // fallback; should rarely matter given K in [0,27]

            int d = rnd.next(0, mx);
            digits.push_back(d);

            last.push_back(d);
            if ((int)last.size() > 2) last.pop_front();
        }
    } else {
        // force failure on the first move: first cell value > K
        int first = rnd.next(K + 1, 9);
        digits.push_back(first);
        for (int i = 2; i <= D - 1; i++) digits.push_back(rnd.next(0, 9));
    }

    // place digits on the path
    for (int i = 1; i <= D - 1; i++) {
        auto [py, px] = path[i];
        if (grid[py][px] == 'S' || grid[py][px] == 'H') continue;
        grid[py][px] = char('0' + digits[i - 1]);
    }

    // output
    println(N, M, K);
    for (auto &row : grid) println(row);
    return 0;
}
