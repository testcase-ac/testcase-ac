#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    constexpr long long MAX_K = 1000000000000000LL;

    vector<long long> anchors = {
        1LL,
        2LL,
        3LL,
        4LL,
        6LL,
        10LL,
        12LL,
        24LL,
        36LL,
        60LL,
        120LL,
        360LL,
        2520LL,
        27720LL,
        360360LL,
        12252240LL,
        232792560LL,
        1000000000LL,
        1000000000000LL,
        MAX_K,
    };

    int caseCount = rnd.next(4, 12);
    vector<long long> values;
    values.reserve(caseCount);

    for (int i = 0; i < caseCount; ++i) {
        int mode = rnd.next(0, 4);
        long long k;

        if (mode == 0) {
            k = rnd.any(anchors);
        } else if (mode == 1) {
            long long base = rnd.any(anchors);
            long long delta = rnd.next(-10LL, 10LL);
            k = max(1LL, min(MAX_K, base + delta));
        } else if (mode == 2) {
            long long high = rnd.any(vector<long long>{
                100LL,
                10000LL,
                1000000LL,
                1000000000LL,
                1000000000000LL,
                MAX_K,
            });
            k = rnd.next(1LL, high);
        } else {
            long long a = rnd.next(1LL, 100000000LL);
            long long b = rnd.next(1LL, 10000000LL);
            k = min(MAX_K, a * b);
        }

        values.push_back(k);
    }

    for (long long k : values) {
        println(k);
    }
    println(0);

    return 0;
}
