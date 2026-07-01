#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

const long long MAX_K = 1000000000000000000LL;

long long clampK(long long value) {
    return max(1LL, min(MAX_K, value));
}

long long randomMaskValue() {
    long long value = 0;
    int highestBit = rnd.next(0, 59);
    for (int bit = 0; bit <= highestBit; ++bit) {
        if (rnd.next(0, 1)) value |= 1LL << bit;
    }
    return clampK(value + 1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> cases;

    cases.push_back(1);
    cases.push_back(2);
    cases.push_back(3);
    cases.push_back(MAX_K);

    int mode = rnd.next(0, 4);
    int targetT = rnd.next(20, 80);

    while ((int)cases.size() < targetT) {
        long long k;
        if (mode == 0) {
            int bit = rnd.next(0, 59);
            long long base = 1LL << bit;
            k = base + rnd.next(-3, 3);
        } else if (mode == 1) {
            int bit = rnd.next(1, 59);
            long long base = (1LL << bit) - 1;
            k = base + rnd.next(-2, 2);
        } else if (mode == 2) {
            k = randomMaskValue();
        } else if (mode == 3) {
            k = rnd.next(1LL, 1000000LL);
        } else {
            long long span = rnd.next(0LL, 1000000LL);
            k = MAX_K - span;
        }
        cases.push_back(clampK(k));
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (long long k : cases) {
        println(k);
    }

    return 0;
}
