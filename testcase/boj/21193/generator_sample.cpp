#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static int countDistinctSumsAtLeastK(const vector<int>& weights, int k) {
    vector<long long> sums = {0};
    for (int weight : weights) {
        vector<long long> next = sums;
        next.reserve(sums.size() * 2);
        for (long long sum : sums) {
            next.push_back(sum + weight);
        }
        sort(next.begin(), next.end());
        next.erase(unique(next.begin(), next.end()), next.end());
        if (static_cast<int>(next.size()) > k) {
            next.resize(k);
        }
        sums.swap(next);
    }
    return static_cast<int>(sums.size());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> weights;
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        int n = rnd.next(1, 12);
        int value = rnd.next(1, 8);
        weights.assign(n, value);
    } else if (mode == 1) {
        int n = rnd.next(2, 12);
        int value = 1;
        for (int i = 0; i < n; ++i) {
            weights.push_back(value);
            value *= 2;
        }
    } else if (mode == 2) {
        int n = rnd.next(5, 18);
        int base = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            weights.push_back(base + rnd.next(0, 5));
        }
    } else if (mode == 3) {
        int n = rnd.next(4, 14);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                weights.push_back(rnd.next(1, 5));
            } else {
                weights.push_back(rnd.next(900000, 1000000));
            }
        }
    } else {
        int n = rnd.next(8, 20);
        for (int i = 0; i < n; ++i) {
            weights.push_back(rnd.next(1, 50));
        }
    }

    shuffle(weights.begin(), weights.end());

    int maxK = countDistinctSumsAtLeastK(weights, 1000);
    int k = rnd.next(1, maxK);

    println(static_cast<int>(weights.size()));
    println(k);
    println(weights);

    return 0;
}
