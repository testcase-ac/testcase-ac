#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 5;
    } else if (mode == 1) {
        n = 40;
    } else {
        n = rnd.next(5, 40);
    }

    int maxCore = min(n, 20);
    int coreSize = maxCore;
    if (mode >= 2 && maxCore > 5) {
        coreSize = rnd.next(5, maxCore);
    }

    vector<long long> values;
    values.reserve(n);

    long long prefixSum = 0;
    for (int i = 0; i < coreSize; ++i) {
        long long slack = (mode == 3 ? rnd.next(0, 3) : rnd.next(0, 20));
        long long value = prefixSum + 1 + slack;
        values.push_back(value);
        prefixSum += value;
    }

    vector<int> chosen(coreSize, 0);
    if (mode == 0) {
        chosen[0] = 1;
    } else if (mode == 4) {
        fill(chosen.begin(), chosen.end(), 1);
    } else if (mode != 5) {
        double pickProbability = rnd.next(0.15, 0.75);
        bool any = false;
        for (int i = 0; i < coreSize; ++i) {
            chosen[i] = rnd.next() < pickProbability;
            any = any || chosen[i];
        }
        if (!any) chosen[rnd.next(0, coreSize - 1)] = 1;
    }

    long long k = 0;
    for (int i = 0; i < coreSize; ++i) {
        if (chosen[i]) k += values[i];
    }

    while ((int)values.size() < n) {
        long long value = k + 1 + rnd.next(0, 1000);
        values.push_back(value);
    }

    shuffle(values.begin(), values.end());

    println(n);
    for (long long value : values) {
        println(value);
    }
    println(k);

    return 0;
}
