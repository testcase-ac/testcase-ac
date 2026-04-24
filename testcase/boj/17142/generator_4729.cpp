#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter for N: small, medium, or max
    double pN = rnd.next();
    int N;
    if (pN < 0.4) {
        N = rnd.next(4, 6);
    } else if (pN < 0.8) {
        N = rnd.next(7, 9);
    } else {
        N = 10;
    }

    int cells = N * N;
    // Hyperparameter for total number of virus spots V0: small, mid, large
    double pV = rnd.next();
    int maxV = min(10, cells - 1);
    int V0;
    if (pV < 0.4) {
        V0 = rnd.next(1, min(3, maxV));
    } else if (pV < 0.8) {
        V0 = rnd.next(4, min(6, maxV));
    } else {
        V0 = rnd.next(min(7, maxV), maxV);
    }
    // Number of active viruses M
    int M = rnd.next(1, V0);

    // Hyperparameter for number of walls
    double pW = rnd.next();
    int wc_low, wc_high;
    if (pW < 0.3) {
        wc_low = 0;
        wc_high = cells / 6;
    } else if (pW < 0.6) {
        wc_low = cells / 6;
        wc_high = cells / 3;
    } else {
        wc_low = cells / 3;
        wc_high = cells - V0;
    }
    // Clip to ensure at least V0 non-wall cells remain
    wc_low = max(0, min(wc_low, cells - V0));
    wc_high = max(0, min(wc_high, cells - V0));
    if (wc_low > wc_high) wc_low = wc_high;
    int wallCount = rnd.next(wc_low, wc_high);

    // Assign positions: walls, viruses, empty
    vector<int> all(cells);
    for (int i = 0; i < cells; i++) all[i] = i;
    shuffle(all.begin(), all.end());

    vector<vector<int>> grid(N, vector<int>(N, 0));
    // walls
    for (int i = 0; i < wallCount; i++) {
        int idx = all[i];
        grid[idx / N][idx % N] = 1;
    }
    // viruses
    for (int i = wallCount; i < wallCount + V0; i++) {
        int idx = all[i];
        grid[idx / N][idx % N] = 2;
    }
    // rest remain 0

    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        println(grid[i]);
    }
    return 0;
}
