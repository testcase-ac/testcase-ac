#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of posters
    int N = rnd.next(1, 10);
    // maximum coordinate (small for hand-check)
    int maxCoord = rnd.any(vector<int>{20, 30, 50, 100});
    vector<pair<int,int>> segs;
    // choose generation mode: 0=random, 1=clusters, 2=nested
    int mode = rnd.next(0, 2);
    if (mode == 0) {
        // fully random intervals
        for (int i = 0; i < N; i++) {
            int l = rnd.next(1, maxCoord - 1);
            int r = rnd.next(l + 1, maxCoord);
            segs.emplace_back(l, r);
        }
    } else if (mode == 1) {
        // cluster intervals around K centers
        int K = rnd.next(1, min(N, 3));
        vector<int> centers;
        for (int i = 0; i < K; i++) {
            centers.push_back(rnd.next(1, maxCoord));
        }
        for (int i = 0; i < N; i++) {
            int c = rnd.any(centers);
            int delta = rnd.next(1, max(1, maxCoord / 10));
            int l = max(1, c - delta);
            int r = min(maxCoord, c + delta);
            if (l >= r) r = l + 1;
            segs.emplace_back(l, r);
        }
    } else {
        // nested intervals: one big and then shrink
        int l = 1, r = maxCoord;
        segs.emplace_back(l, r);
        for (int i = 1; i < N; i++) {
            int len = r - l;
            if (len <= 1) {
                // fallback to random
                int a = rnd.next(1, maxCoord - 1);
                int b = rnd.next(a + 1, maxCoord);
                segs.emplace_back(a, b);
            } else {
                int shrinkL = rnd.next(0, len/2);
                int shrinkR = rnd.next(0, len/2);
                l = l + shrinkL;
                r = r - shrinkR;
                if (r - l < 1) {
                    int a = rnd.next(1, maxCoord - 1);
                    int b = rnd.next(a + 1, maxCoord);
                    segs.emplace_back(a, b);
                } else {
                    segs.emplace_back(l, r);
                }
            }
        }
    }
    // shuffle order to mix patterns
    shuffle(segs.begin(), segs.end());
    // output
    println(N);
    for (auto &p : segs) {
        println(p.first, p.second);
    }
    return 0;
}
