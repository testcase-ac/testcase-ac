#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long randomValue(long long lo, long long hi) {
    return rnd.next(lo, hi);
}

vector<long long> randomArray(int n, long long lo, long long hi) {
    vector<long long> values(n);
    for (long long& value : values) {
        value = randomValue(lo, hi);
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_VALUE = 1000000000LL;
    int mode = rnd.next(0, 4);
    int n;
    long long t;
    vector<long long> weights;
    vector<long long> distances;
    vector<long long> prices;

    if (mode == 0) {
        n = rnd.next(2, 8);
        t = randomValue(1, 10);
        weights = randomArray(n, 1, 40);
        distances = randomArray(n, 1, 40);
        prices = randomArray(n, 1, 80);
    } else if (mode == 1) {
        n = rnd.next(3, 10);
        t = randomValue(1, 20);
        weights.resize(n);
        distances.resize(n);
        prices.resize(n);
        long long baseWeight = randomValue(1, 20);
        long long baseDistance = randomValue(1, 20);
        long long baseProfit = randomValue(1, 200);
        for (int i = 0; i < n; ++i) {
            weights[i] = baseWeight + i * randomValue(1, 5);
            distances[i] = baseDistance + i * randomValue(1, 5);
            prices[i] = baseProfit + distances[i] * t;
        }
        shuffle(weights.begin(), weights.end());
        shuffle(distances.begin(), distances.end());
        shuffle(prices.begin(), prices.end());
    } else if (mode == 2) {
        n = rnd.next(4, 12);
        t = randomValue(1, 1000000);
        weights = randomArray(n, 1, MAX_VALUE);
        distances = randomArray(n, 1, 1000);
        prices.resize(n);
        long long commonProfit = randomValue(1, 1000000);
        for (int i = 0; i < n; ++i) {
            prices[i] = min(MAX_VALUE, distances[i] * t + commonProfit);
        }
    } else if (mode == 3) {
        n = rnd.next(2, 8);
        t = randomValue(100000000, MAX_VALUE);
        weights = randomArray(n, 1, MAX_VALUE);
        distances = randomArray(n, 1, MAX_VALUE);
        prices = randomArray(n, 1, MAX_VALUE);
    } else {
        n = rnd.next(6, 20);
        t = randomValue(1, 1000);
        weights.resize(n);
        distances.resize(n);
        prices.resize(n);
        for (int i = 0; i < n; ++i) {
            weights[i] = 1 + (i % 3) * randomValue(1, 10);
            distances[i] = 1 + (i % 4) * randomValue(1, 20);
            prices[i] = 1 + (i % 5) * randomValue(1, 30);
        }
        shuffle(weights.begin(), weights.end());
        shuffle(distances.begin(), distances.end());
        shuffle(prices.begin(), prices.end());
    }

    println(n, t);
    println(weights);
    println(distances);
    println(prices);

    return 0;
}
