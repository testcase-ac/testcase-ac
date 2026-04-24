#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cows
    int N = rnd.next(2, 10);
    // Ranges for coordinates, at least N to ensure distinctness
    int rangeX = rnd.next(N, 20);
    int rangeY = rnd.next(N, 20);

    // Hyper-parameter to bias number of north-facing cows
    int tBias = rnd.next(-2, 2);
    int northCount = rnd.wnext(N + 1, tBias); // in [0..N]

    // Prepare direction list
    vector<char> dirs;
    for (int i = 0; i < northCount; i++) dirs.push_back('N');
    for (int i = 0; i < N - northCount; i++) dirs.push_back('E');
    shuffle(dirs.begin(), dirs.end());

    // Generate distinct x-coordinates
    vector<int> xs(rangeX);
    iota(xs.begin(), xs.end(), 0);
    shuffle(xs.begin(), xs.end());
    xs.resize(N);

    // Generate distinct y-coordinates
    vector<int> ys(rangeY);
    iota(ys.begin(), ys.end(), 0);
    shuffle(ys.begin(), ys.end());
    ys.resize(N);

    // Shuffle the order of cows for input variety
    vector<int> order(N);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end());

    // Output
    println(N);
    for (int idx : order) {
        printf("%c %d %d\n", dirs[idx], xs[idx], ys[idx]);
    }

    return 0;
}
