#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int YMAX = 20; // keep coordinates small and readable

    int scenario = rnd.next(1, 5);

    int H;              // number of horizontal segments
    vector<int> h;      // heights (y-coordinates) of horizontals, 1..H
    vector<int> dx;     // lengths of horizontals, 1..H

    if (scenario == 1) {
        // Simple rectangle
        H = 1;
        h.assign(H + 1, 0);
        dx.assign(H + 1, 0);

        h[1] = rnd.next(2, YMAX);      // depth
        dx[1] = rnd.next(2, 15);       // width
    } else if (scenario == 2) {
        // Monotone increasing depth to the right
        H = rnd.next(2, 6);
        h.assign(H + 1, 0);
        dx.assign(H + 1, 0);

        int maxStep = max(1, (YMAX - 1) / (H - 1)); // (H-1)*step <= YMAX-1
        int step = rnd.next(1, maxStep);
        int minH = rnd.next(1, YMAX - (H - 1) * step);

        for (int i = 1; i <= H; i++) {
            h[i] = minH + (i - 1) * step;
        }
        for (int i = 1; i <= H; i++) {
            dx[i] = rnd.next(1, 8);
        }
    } else if (scenario == 3) {
        // Monotone decreasing depth to the right
        H = rnd.next(2, 6);
        h.assign(H + 1, 0);
        dx.assign(H + 1, 0);

        int maxStep = max(1, (YMAX - 1) / (H - 1)); // (H-1)*step <= YMAX-1
        int step = rnd.next(1, maxStep);
        int minMaxH = 1 + (H - 1) * step;           // ensure last height >= 1
        int maxMaxH = YMAX;
        if (minMaxH > maxMaxH) minMaxH = maxMaxH;   // just in case
        int maxH = rnd.next(minMaxH, maxMaxH);

        for (int i = 1; i <= H; i++) {
            h[i] = maxH - (i - 1) * step;
        }
        for (int i = 1; i <= H; i++) {
            dx[i] = rnd.next(1, 8);
        }
    } else if (scenario == 4) {
        // Zigzag high/low pattern (multiple basins)
        H = rnd.next(3, 8);
        h.assign(H + 1, 0);
        dx.assign(H + 1, 0);

        int low = rnd.next(1, 8);
        int high;
        do {
            high = rnd.next(2, YMAX);
        } while (high <= low);

        bool startLow = rnd.next(0, 1) == 0;
        for (int i = 1; i <= H; i++) {
            if ((i % 2 == 1) == startLow) h[i] = low;
            else h[i] = high;
        }
        for (int i = 1; i <= H; i++) {
            dx[i] = rnd.next(1, 6);
        }
    } else {
        // Random walk with bounded steps, no equal adjacent heights
        H = rnd.next(2, 8);
        h.assign(H + 1, 0);
        dx.assign(H + 1, 0);

        h[1] = rnd.next(2, YMAX - 1);
        for (int i = 2; i <= H; i++) {
            int cur = h[i - 1];
            vector<int> cand;
            for (int delta = -4; delta <= 4; delta++) {
                if (delta == 0) continue;
                int v = cur + delta;
                if (v >= 1 && v <= YMAX) cand.push_back(v);
            }
            h[i] = rnd.any(cand);
        }
        for (int i = 1; i <= H; i++) {
            dx[i] = rnd.next(1, 8);
        }
    }

    // Build vertices: start at (0,0), alternate vertical/horizontal, end at (A,0)
    vector<pair<int,int>> V;
    V.reserve(2 * H + 2);
    int xcur = 0;

    V.push_back({0, 0}); // first vertex

    for (int i = 1; i <= H; i++) {
        // Vertical segment
        V.push_back({xcur, h[i]});
        // Horizontal segment
        xcur += dx[i];
        V.push_back({xcur, h[i]});
    }
    // Final vertical back to surface
    V.push_back({xcur, 0});

    int N = (int)V.size(); // number of vertices
    int Hverify = (N - 2) / 2; // should equal H

    // Analyze heights for hole placement strategies
    int minH = h[1], maxH = h[1];
    for (int i = 2; i <= H; i++) {
        if (h[i] < minH) minH = h[i];
        if (h[i] > maxH) maxH = h[i];
    }
    vector<int> minIdx, maxIdx; // 0-based horizontal indices
    for (int i = 1; i <= H; i++) {
        if (h[i] == minH) minIdx.push_back(i - 1);
        if (h[i] == maxH) maxIdx.push_back(i - 1);
    }

    int strategy = rnd.next(0, 3); // 0: random subset, 1: all mins, 2: all maxs, 3: min+max
    vector<int> holesIndices;

    if (strategy == 0) {
        vector<int> cand(Hverify);
        for (int i = 0; i < Hverify; i++) cand[i] = i;
        shuffle(cand.begin(), cand.end());
        int maxK = min(Hverify, 4);
        int K = rnd.next(1, maxK);
        holesIndices.assign(cand.begin(), cand.begin() + K);
    } else if (strategy == 1) {
        holesIndices = minIdx; // at least one always
    } else if (strategy == 2) {
        holesIndices = maxIdx; // at least one always
    } else {
        // Try to choose one min and one max (distinct). If impossible, fall back to random subset.
        if (minH != maxH && !minIdx.empty() && !maxIdx.empty()) {
            int a = rnd.any(minIdx);
            int b = rnd.any(maxIdx);
            if (a == b) {
                bool fixed = false;
                for (int x : maxIdx) if (x != a) { b = x; fixed = true; break; }
                if (!fixed) {
                    for (int x : minIdx) if (x != b) { a = x; fixed = true; break; }
                }
                if (!fixed) {
                    vector<int> cand(Hverify);
                    for (int i = 0; i < Hverify; i++) cand[i] = i;
                    shuffle(cand.begin(), cand.end());
                    int maxK = min(Hverify, 4);
                    int K = rnd.next(1, maxK);
                    holesIndices.assign(cand.begin(), cand.begin() + K);
                } else {
                    holesIndices = {a, b};
                }
            } else {
                holesIndices = {a, b};
            }
        } else {
            vector<int> cand(Hverify);
            for (int i = 0; i < Hverify; i++) cand[i] = i;
            shuffle(cand.begin(), cand.end());
            int maxK = min(Hverify, 4);
            int K = rnd.next(1, maxK);
            holesIndices.assign(cand.begin(), cand.begin() + K);
        }
    }

    if (holesIndices.empty()) {
        // Guarantee at least one hole
        holesIndices.push_back(rnd.next(0, Hverify - 1));
    }

    shuffle(holesIndices.begin(), holesIndices.end());
    int K = (int)holesIndices.size();

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        println(V[i].first, V[i].second);
    }

    println(K);
    for (int idx : holesIndices) {
        int vi = 2 * idx + 1; // starting vertex of this horizontal segment
        int x1 = V[vi].first;
        int y  = V[vi].second;
        int x2 = V[vi + 1].first;
        println(x1, y, x2, y);
    }

    return 0;
}
