#include "testlib.h"
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size hyper-parameter
    int n = rnd.next(1, 10);
    int m = rnd.next(1, min(n, 5));

    // Coordinate spacing hyper-parameter
    int incMax = rnd.next(1, 20);

    // Clustering probability hyper-parameter for colors
    double clusterProb = rnd.next();

    // Generate strictly increasing coordinates
    vector<long long> coords(n);
    coords[0] = rnd.next(0, 10);
    for (int i = 1; i < n; i++) {
        coords[i] = coords[i-1] + rnd.next(1, incMax);
    }

    // Prepare color assignment, ensuring each color appears at least once
    vector<int> colors(n, -1);
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    shuffle(idx.begin(), idx.end());
    for (int c = 1; c <= m; c++) {
        colors[idx[c-1]] = c;
    }

    // Assign remaining colors with possible clustering
    for (int i = 0; i < n; i++) {
        if (colors[i] == -1) {
            if (i > 0 && rnd.next() < clusterProb) {
                colors[i] = colors[i-1];
            } else {
                colors[i] = rnd.next(1, m);
            }
        }
    }

    // Output
    println(m, n);
    println(coords);
    println(colors);

    return 0;
}
