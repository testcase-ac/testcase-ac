#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of chapters (items)
    int N = rnd.next(1, 10);

    // Hyper-parameter: choose weight scale mode
    bool smallWeights = rnd.next(0, 1) == 0;

    // Generate weights K_i
    vector<int> K(N);
    for (int i = 0; i < N; i++) {
        if (smallWeights) {
            K[i] = rnd.next(1, 100);
        } else {
            K[i] = rnd.next(500, 1000);
        }
    }

    // Compute some sums for capacity selection
    int sumK = accumulate(K.begin(), K.end(), 0);
    int sumK2 = max(1, sumK / 2);

    // Hyper-parameter: choose capacity T to be small or large
    int T;
    if (rnd.next(0, 1) == 0) {
        // small capacity
        T = rnd.next(1, sumK2);
    } else {
        // large capacity
        T = rnd.next(sumK2, sumK);
    }
    T = min(T, 10000); // respect limits

    // Hyper-parameter: correlation between weight and score
    double corr;
    int corrType = rnd.next(0, 2);
    if (corrType == 0) {
        corr = 0.0;
    } else if (corrType == 1) {
        corr = 1.0;
    } else {
        corr = rnd.next(1, 99) / 100.0;
    }

    // Normalize factor for weights -> base scores
    int maxK = *max_element(K.begin(), K.end());

    // Build items with biased scores
    vector<pair<int,int>> items(N);
    for (int i = 0; i < N; i++) {
        double base1 = (double)K[i] * 1000.0 / maxK;
        double base2 = rnd.next(1, 1000);
        int Si = int(round(corr * base1 + (1 - corr) * base2));
        Si = min(max(Si, 1), 1000);
        items[i] = {K[i], Si};
    }

    // Shuffle order of items
    shuffle(items.begin(), items.end());

    // Output
    println(N, T);
    for (auto &p : items) {
        println(p.first, p.second);
    }

    return 0;
}
