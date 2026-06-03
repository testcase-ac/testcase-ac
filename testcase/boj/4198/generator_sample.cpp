#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_WEIGHT = 2147483647;

void printWeights(const vector<int>& weights) {
    println((int)weights.size());
    for (int weight : weights) {
        println(weight);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 0;
    if (mode == 0) {
        n = rnd.next(0, 2);
    } else {
        n = rnd.next(3, 18);
    }

    vector<int> weights;
    weights.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            weights.push_back(rnd.next(0, MAX_WEIGHT));
        }
    } else if (mode == 1) {
        int start = rnd.next(0, 100);
        int step = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            weights.push_back(start + i * step);
        }
    } else if (mode == 2) {
        int start = rnd.next(0, 100);
        int step = rnd.next(1, 20);
        for (int i = n - 1; i >= 0; --i) {
            weights.push_back(start + i * step);
        }
    } else if (mode == 3) {
        int low = rnd.next(0, 50);
        int high = low + n + rnd.next(20, 80);
        int pivot = rnd.next(1, n - 2);
        for (int i = 0; i < pivot; ++i) {
            weights.push_back(low + i * 2);
        }
        for (int i = pivot; i < n; ++i) {
            weights.push_back(high - (i - pivot) * 2);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            weights.push_back(i);
        }
        shuffle(weights.begin(), weights.end());
    } else {
        for (int i = 0; i < n; ++i) {
            weights.push_back(MAX_WEIGHT - i);
        }
        shuffle(weights.begin(), weights.end());
    }

    printWeights(weights);
    return 0;
}
