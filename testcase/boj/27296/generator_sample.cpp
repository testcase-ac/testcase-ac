#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_N = 1000000000000000000LL;
    vector<long long> values = {0, 1, 2, 3};

    int mode = rnd.next(0, 4);
    int targetT = rnd.next(8, 30);

    if (mode == 0) {
        while ((int)values.size() < targetT) {
            values.push_back(rnd.next(0LL, 12LL));
        }
    } else if (mode == 1) {
        vector<long long> boundaries = {
            4,
            5,
            10,
            100,
            MAX_N - 3,
            MAX_N - 2,
            MAX_N - 1,
            MAX_N
        };
        values.insert(values.end(), boundaries.begin(), boundaries.end());
        while ((int)values.size() < targetT) {
            long long delta = rnd.next(0LL, 1000000LL);
            values.push_back(MAX_N - delta);
        }
    } else if (mode == 2) {
        long long x = 1;
        while ((int)values.size() < targetT && x <= MAX_N / 2) {
            x *= 2;
            long long jitter = rnd.next(0LL, min(5LL, x));
            values.push_back(min(MAX_N, x + jitter));
        }
        while ((int)values.size() < targetT) {
            values.push_back(rnd.next(0LL, MAX_N));
        }
    } else if (mode == 3) {
        while ((int)values.size() < targetT) {
            long long base = rnd.next(0LL, 1000000000LL);
            values.push_back(base * base);
        }
    } else {
        while ((int)values.size() < targetT) {
            values.push_back(rnd.next(0LL, MAX_N));
        }
    }

    shuffle(values.begin(), values.end());

    println((int)values.size());
    for (long long n : values) {
        println(n);
    }

    return 0;
}
