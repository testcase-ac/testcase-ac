#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: choose coordinate range
    vector<int> ranges = {2, 3, 4, 5, 6};
    int rangeBound = rnd.any(ranges);
    // Start position
    int sx = rnd.next(-rangeBound, rangeBound);
    int sy = rnd.next(-rangeBound, rangeBound);
    // Home position, distinct
    int hx, hy;
    do {
        hx = rnd.next(-rangeBound, rangeBound);
        hy = rnd.next(-rangeBound, rangeBound);
    } while (hx == sx && hy == sy);
    // Padding for obstacle candidate area
    int pad = rnd.next(1, 3);
    int minX = min(sx, hx) - pad;
    int maxX = max(sx, hx) + pad;
    int minY = min(sy, hy) - pad;
    int maxY = max(sy, hy) + pad;
    // Time limit based on Manhattan distance plus slack
    int manDist = abs(sx - hx) + abs(sy - hy);
    int slack = rnd.next(0, pad + rangeBound);
    int T = rnd.next(manDist, manDist + slack);
    // Build candidate obstacle positions
    vector<pair<int,int>> cand;
    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            if ((x == sx && y == sy) || (x == hx && y == hy)) continue;
            cand.emplace_back(x, y);
        }
    }
    shuffle(cand.begin(), cand.end());
    // Choose number of obstacles
    int maxObs = rnd.next(0, 10);
    int N = rnd.next(0, min((int)cand.size(), maxObs));
    // Output
    println(sx, sy);
    println(T);
    println(hx, hy);
    println(N);
    for (int i = 0; i < N; i++) {
        println(cand[i].first, cand[i].second);
    }
    return 0;
}
