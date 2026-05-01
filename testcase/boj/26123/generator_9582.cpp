#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 9);

    int N = 1;
    int D = 1;
    vector<int> h;

    switch (scenario) {
        case 0: { // single building
            N = 1;
            int H0 = rnd.next(1, 50);
            int mode0 = rnd.next(0, 2);
            if (mode0 == 0 && H0 > 1) {
                D = rnd.next(1, H0 - 1);
            } else if (mode0 == 1) {
                D = H0;
            } else {
                D = H0 + rnd.next(1, 20);
                if (D > 300000) D = 300000;
            }
            h.assign(1, H0);
            break;
        }
        case 1: { // all equal heights
            N = rnd.next(2, 7);
            int H = rnd.next(2, 30);
            h.assign(N, H);
            int mode = rnd.next(0, 2);
            if (mode == 0 && H > 1) {
                D = rnd.next(1, H - 1);
            } else if (mode == 1) {
                D = H;
            } else {
                D = H + rnd.next(1, 20);
                if (D > 300000) D = 300000;
            }
            break;
        }
        case 2: { // random small
            N = rnd.next(2, 10);
            int maxH = rnd.next(5, 30);
            h.resize(N);
            for (int i = 0; i < N; ++i)
                h[i] = rnd.next(1, maxH);
            D = rnd.next(1, maxH + 5);
            if (D > 300000) D = 300000;
            break;
        }
        case 3: { // staircase increasing
            N = rnd.next(5, 15);
            int base = rnd.next(1, 3);
            h.resize(N);
            for (int i = 0; i < N; ++i)
                h[i] = base + i;
            int maxH = base + N - 1;
            int mode = rnd.next(0, 2);
            if (mode == 0) D = maxH;
            else if (mode == 1) D = max(1, maxH / 2);
            else {
                D = maxH + rnd.next(1, 5);
                if (D > 300000) D = 300000;
            }
            break;
        }
        case 4: { // staircase decreasing
            N = rnd.next(5, 15);
            int base = rnd.next(1, 3);
            h.resize(N);
            for (int i = 0; i < N; ++i)
                h[i] = base + (N - 1 - i);
            int maxH = base + N - 1;
            int mode = rnd.next(0, 2);
            if (mode == 0) D = maxH;
            else if (mode == 1) D = max(1, maxH - 2);
            else {
                D = maxH + rnd.next(1, 5);
                if (D > 300000) D = 300000;
            }
            break;
        }
        case 5: { // single spike
            N = rnd.next(5, 15);
            int spikeIdx = rnd.next(0, N - 1);
            int lowH = rnd.next(1, 5);
            int highH = rnd.next(10, 40);
            h.assign(N, lowH);
            h[spikeIdx] = highH;
            int mode = rnd.next(0, 2);
            if (mode == 0 && highH > 1) {
                D = rnd.next(1, highH - 1);
            } else if (mode == 1) {
                D = highH;
            } else {
                D = highH + rnd.next(1, 10);
                if (D > 300000) D = 300000;
            }
            break;
        }
        case 6: { // alternating high/low
            N = rnd.next(4, 14);
            int lo = rnd.next(1, 5);
            int hi = rnd.next(lo + 1, lo + 10);
            h.resize(N);
            for (int i = 0; i < N; ++i)
                h[i] = (i % 2 == 0 ? hi : lo);
            int mode = rnd.next(0, 2);
            if (mode == 0 && hi > 1) {
                D = rnd.next(1, hi - 1);
            } else if (mode == 1) {
                D = hi;
            } else {
                D = hi + rnd.next(1, 10);
                if (D > 300000) D = 300000;
            }
            break;
        }
        case 7: { // random medium, D > maxH
            N = rnd.next(10, 20);
            int maxHCap = rnd.next(10, 40);
            h.resize(N);
            int maxH = 0;
            for (int i = 0; i < N; ++i) {
                h[i] = rnd.next(1, maxHCap);
                if (h[i] > maxH) maxH = h[i];
            }
            int extra = rnd.next(1, 10);
            long long tD = (long long)maxH + extra;
            if (tD > 300000) tD = 300000;
            D = (int)tD;
            break;
        }
        case 8: { // tall buildings, small N
            N = rnd.next(2, 8);
            int maxCap = rnd.next(50000, 300000);
            h.resize(N);
            int maxH = 0;
            for (int i = 0; i < N; ++i) {
                h[i] = rnd.wnext(maxCap, 3) + 1; // biased to larger values
                if (h[i] > maxH) maxH = h[i];
            }
            int offset = rnd.next(-5, 5);
            long long tD = (long long)maxH + offset;
            if (tD < 1) tD = 1;
            if (tD > 300000) tD = 300000;
            D = (int)tD;
            break;
        }
        case 9: default: { // wide random within full constraints but small N
            N = rnd.next(1, 20);
            h.resize(N);
            for (int i = 0; i < N; ++i)
                h[i] = rnd.next(1, 300000);
            D = rnd.next(1, 300000);
            break;
        }
    }

    println(N, D);
    println(h);

    return 0;
}
