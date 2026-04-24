#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Sample N with variability: small, medium, large within [5,20]
    double p = rnd.next();
    int N;
    if (p < 0.3) {
        N = rnd.next(5, 8);
    } else if (p < 0.6) {
        N = rnd.next(9, 12);
    } else {
        N = rnd.next(13, 20);
    }
    // Sample W (number of events) relative to N, biased for small/medium/large
    int maxW = min(3 * N, 30);
    double q = rnd.next();
    int W;
    if (q < 0.4) {
        W = rnd.next(1, min(5, maxW));
    } else if (q < 0.8) {
        W = rnd.next(min(6, maxW), min(maxW, 2 * N));
    } else {
        W = rnd.next(min(2 * N + 1, maxW), maxW);
    }
    // Build events: some clustered near a random corner, others uniform
    vector<pair<int,int>> events;
    int c = rnd.next(0, W); // number of clustered events
    int corner = rnd.next(1, 4);
    int bx = (corner == 1 || corner == 2) ? 1 : N;
    int by = (corner == 1 || corner == 3) ? 1 : N;
    for (int i = 0; i < c; i++) {
        int dx = rnd.next(-1, 1);
        int dy = rnd.next(-1, 1);
        int x = min(max(1, bx + dx), N);
        int y = min(max(1, by + dy), N);
        events.emplace_back(x, y);
    }
    for (int i = c; i < W; i++) {
        int x = rnd.next(1, N);
        int y = rnd.next(1, N);
        events.emplace_back(x, y);
    }
    shuffle(events.begin(), events.end());
    // Output the test case
    println(N);
    println(W);
    for (auto &e : events) {
        println(e.first, e.second);
    }
    return 0;
}
