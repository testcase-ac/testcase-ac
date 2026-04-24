#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of cities
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // Distances between adjacent cities: N-1 values
    vector<int> dist = inf.readInts(N - 1, 1, 1000000000, "dist_i");
    inf.readEoln();
    int sm = 0;
    const int DIST_SUM_MAX = 1e9;
    for(int i=0; i<N-1; i++) {
        sm += dist[i];
        ensuref(sm <= 1e9, "Sum of edge length must not be greater than 10^9, but it is already %d after %d edges", sm, i+1);
    }

    // Prices at each city: N values
    vector<int> price = inf.readInts(N, 1, 1000000000, "price_i");
    inf.readEoln();

    // No other global conditions to check
    inf.readEof();
    return 0;
}
