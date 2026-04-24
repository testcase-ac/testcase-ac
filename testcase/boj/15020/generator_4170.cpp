#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small grid size
    int h = rnd.next(1, 10);
    int w = rnd.next(1, 10);

    // Hyper-parameters for diversity
    double pNeg = rnd.next(0.0, 1.0);        // probability of water cell
    int maxDepth = rnd.next(1, 5);           // maximum water depth
    int maxLandAlt = rnd.next(0, 5);         // maximum land altitude

    vector<vector<int>> a(h, vector<int>(w));
    vector<pair<int,int>> waterCells;

    // Generate grid
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (rnd.next() < pNeg) {
                int d = rnd.next(1, maxDepth);
                a[i][j] = -d;
                waterCells.emplace_back(i, j);
            } else {
                a[i][j] = rnd.next(0, maxLandAlt);
            }
        }
    }
    // Ensure at least one water cell
    if (waterCells.empty()) {
        int i = rnd.next(0, h-1);
        int j = rnd.next(0, w-1);
        int d = rnd.next(1, maxDepth);
        a[i][j] = -d;
        waterCells.emplace_back(i, j);
    }

    // Choose device location
    auto dev = rnd.any(waterCells);
    int di = dev.first, dj = dev.second;

    // Output
    println(h, w);
    for (int i = 0; i < h; i++) {
        println(a[i]);
    }
    // 1-based indexing for device
    println(di+1, dj+1);

    return 0;
}
