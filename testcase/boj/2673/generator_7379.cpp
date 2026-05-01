#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N with variability: small, mid, large
    double p = rnd.next();
    int N;
    if (p < 0.2) {
        N = rnd.next(1, 4);
    } else if (p < 0.6) {
        N = rnd.next(5, 15);
    } else {
        N = rnd.next(16, 50);
    }
    // Prepare 100 points
    vector<int> pts(100);
    for (int i = 0; i < 100; i++) pts[i] = i + 1;
    shuffle(pts.begin(), pts.end());
    // Take first 2N points
    pts.resize(2 * N);
    // Decide pairing mode
    int mode = rnd.next(3); // 0,1,2
    vector<pair<int,int>> chords;
    if (mode == 0) {
        // random pairing
        for (int i = 0; i < 2 * N; i += 2) {
            chords.emplace_back(pts[i], pts[i+1]);
        }
    } else if (mode == 1) {
        // nested pairing: sort and pair outer-to-inner
        sort(pts.begin(), pts.end());
        for (int i = 0; i < N; i++) {
            chords.emplace_back(pts[i], pts[2*N-1-i]);
        }
    } else {
        // adjacent pairing: sort and pair neighbors
        sort(pts.begin(), pts.end());
        for (int i = 0; i < 2 * N; i += 2) {
            chords.emplace_back(pts[i], pts[i+1]);
        }
    }
    // Shuffle output order
    shuffle(chords.begin(), chords.end());
    // Print
    println(N);
    for (auto &c : chords) {
        println(c.first, c.second);
    }
    return 0;
}
