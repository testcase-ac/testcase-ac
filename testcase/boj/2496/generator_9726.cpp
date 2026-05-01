#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N, M, T, K;

    // Choose scenario type for dimensions
    int scenarioType = rnd.next(0, 9);
    if (scenarioType <= 4) {
        // small map, very readable
        N = rnd.next(1, 15);
        M = rnd.next(1, 15);
    } else if (scenarioType <= 7) {
        // medium map
        N = rnd.next(10, 50);
        M = rnd.next(10, 50);
    } else {
        // large coordinates to test overflow and bounds handling
        N = rnd.next(100000, 1000000);
        M = rnd.next(100000, 1000000);
    }

    int maxDim = max(N, M);
    const int maxK = 10000000;

    // Choose K (even, between 2 and 1e7) with different patterns
    int kType = rnd.next(0, 4);
    if (kType == 0) {
        K = 2; // minimum possible
    } else if (kType == 1) {
        int hi = max(2, min(maxDim, maxK));
        int hi2 = hi / 2;
        int k2 = rnd.next(1, hi2);
        K = 2 * k2;
    } else if (kType == 2) {
        int hi = max(2, min(2 * maxDim, maxK));
        int hi2 = hi / 2;
        int k2 = rnd.next(1, hi2);
        K = 2 * k2;
    } else if (kType == 3) {
        // anywhere in full allowed range
        int hi2 = maxK / 2;
        int k2 = rnd.next(1, hi2);
        K = 2 * k2;
    } else {
        // around map scale
        long long approx = maxDim;
        long long lo2 = max(1LL, approx / 2);
        long long hi2 = min((long long)maxK / 2, approx * 2);
        if (lo2 > hi2) swap(lo2, hi2);
        int k2 = rnd.next((int)lo2, (int)hi2);
        K = 2 * k2;
    }

    // Choose T (number of diamonds) small but variable, never exceeding grid size
    long long cells = (long long)(N + 1) * (M + 1);
    long long cap = min(25LL, cells);
    int T_hi = (int)cap;
    int T_lo;
    if (maxDim <= 10) T_lo = 1;
    else if (maxDim <= 30) T_lo = min(5, T_hi);
    else T_lo = min(10, T_hi);
    if (T_lo > T_hi) T_lo = T_hi;
    T = rnd.next(T_lo, T_hi);

    // Point pattern type
    int pattern = rnd.next(0, 5);

    vector<pair<int, int>> pts;
    pts.reserve(T);
    unordered_set<long long> used;
    used.reserve(T * 2);

    auto encode = [](int x, int y) -> long long {
        return ((long long)x << 32) | (unsigned long long)y;
    };

    auto tryAdd = [&](int x, int y) -> bool {
        if (x < 0 || x > N || y < 0 || y > M) return false;
        long long key = encode(x, y);
        if (used.insert(key).second) {
            pts.push_back({x, y});
            return true;
        }
        return false;
    };

    // Helper: fill remaining points randomly
    auto fillRandom = [&]() {
        while ((int)pts.size() < T) {
            int x = rnd.next(0, N);
            int y = rnd.next(0, M);
            tryAdd(x, y);
        }
    };

    switch (pattern) {
        case 0: {
            // Completely random distinct points
            fillRandom();
            break;
        }
        case 1: {
            // Clustered around a random center
            int cx = rnd.next(0, N);
            int cy = rnd.next(0, M);
            int radiusX = max(1, N / 4);
            int radiusY = max(1, M / 4);
            int target = max(1, T * 2 / 3);
            int attempts = 0;
            while ((int)pts.size() < target && attempts < 1000) {
                int dx = rnd.next(-radiusX, radiusX);
                int dy = rnd.next(-radiusY, radiusY);
                long long nx = (long long)cx + dx;
                long long ny = (long long)cy + dy;
                if (nx < 0 || nx > N || ny < 0 || ny > M) {
                    attempts++;
                    continue;
                }
                tryAdd((int)nx, (int)ny);
                attempts++;
            }
            fillRandom();
            break;
        }
        case 2: {
            // Points mostly on a vertical or horizontal line
            bool vertical = (rnd.next(0, 1) == 0);
            int target = max(1, T * 2 / 3);
            int attempts = 0;
            if (vertical) {
                int x0 = rnd.next(0, N);
                while ((int)pts.size() < target && attempts < 1000) {
                    int y = rnd.next(0, M);
                    tryAdd(x0, y);
                    attempts++;
                }
            } else {
                int y0 = rnd.next(0, M);
                while ((int)pts.size() < target && attempts < 1000) {
                    int x = rnd.next(0, N);
                    tryAdd(x, y0);
                    attempts++;
                }
            }
            fillRandom();
            break;
        }
        case 3: {
            // Points mostly on a diagonal (x + y = const or x - y = const)
            int diagType = rnd.next(0, 1);
            int target = max(1, T * 2 / 3);
            int attempts = 0;
            if (diagType == 0) {
                // x + y = s
                int s = rnd.next(0, N + M);
                while ((int)pts.size() < target && attempts < 2000) {
                    int minY = max(0, s - N);
                    int maxY = min(M, s);
                    if (minY > maxY) break;
                    int y = rnd.next(minY, maxY);
                    int x = s - y;
                    tryAdd(x, y);
                    attempts++;
                }
            } else {
                // x - y = d
                int d = rnd.next(-M, N);
                while ((int)pts.size() < target && attempts < 2000) {
                    int minX = max(0, d);
                    int maxX = min(N, M + d);
                    if (minX > maxX) break;
                    int x = rnd.next(minX, maxX);
                    int y = x - d;
                    tryAdd(x, y);
                    attempts++;
                }
            }
            fillRandom();
            break;
        }
        case 4: {
            // Many points on the boundary of the map
            int target = max(1, T * 2 / 3);
            int attempts = 0;
            while ((int)pts.size() < target && attempts < 2000) {
                int edge = rnd.next(0, 3);
                int x, y;
                if (edge == 0) { // bottom y=0
                    y = 0;
                    x = rnd.next(0, N);
                } else if (edge == 1) { // top y=M
                    y = M;
                    x = rnd.next(0, N);
                } else if (edge == 2) { // left x=0
                    x = 0;
                    y = rnd.next(0, M);
                } else { // right x=N
                    x = N;
                    y = rnd.next(0, M);
                }
                tryAdd(x, y);
                attempts++;
            }
            fillRandom();
            break;
        }
        case 5: {
            // Points clustered near corners
            int attempts = 0;
            while ((int)pts.size() < T && attempts < 2000) {
                int corner = rnd.next(0, 3); // 0:(0,0) 1:(N,0) 2:(0,M) 3:(N,M)
                int baseX = (corner & 1) ? N : 0;
                int baseY = (corner & 2) ? M : 0;
                int maxDx = min(2, N);
                int maxDy = min(2, M);
                int dx = rnd.next(0, maxDx);
                int dy = rnd.next(0, maxDy);
                int x = (baseX == 0) ? baseX + dx : baseX - dx;
                int y = (baseY == 0) ? baseY + dy : baseY - dy;
                tryAdd(x, y);
                attempts++;
            }
            fillRandom();
            break;
        }
        default: {
            fillRandom();
            break;
        }
    }

    println(N, M, T, K);
    for (auto &p : pts) {
        println(p.first, p.second);
    }

    return 0;
}
