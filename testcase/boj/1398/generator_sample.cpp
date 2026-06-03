#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long bounded(long long value) {
    return min(1000000000000000LL, max(1LL, value));
}

void addNear(vector<long long>& values, long long center) {
    int span = rnd.next(0, 30);
    for (int delta = -span; delta <= span; delta += max(1, rnd.next(1, 5))) {
        values.push_back(bounded(center + delta));
    }
}

long long randomChunkedPrice() {
    int chunks = rnd.next(1, 8);
    long long value = rnd.next(1, 99);
    for (int i = 1; i < chunks; ++i) {
        value = value * 100 + rnd.next(0, 99);
    }
    return bounded(value);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> values;

    int target = rnd.next(8, 35);
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        for (int i = 0; i < target; ++i) {
            values.push_back(rnd.next(1, 300));
        }
    } else if (mode == 1) {
        long long power10 = 1;
        for (int k = 0; k <= 15; ++k) {
            values.push_back(power10);
            if (power10 <= 40000000000000LL) values.push_back(25 * power10);
            addNear(values, power10);
            if (power10 <= 40000000000000LL) addNear(values, 25 * power10);
            power10 *= 10;
        }
    } else if (mode == 2) {
        long long power100 = 1;
        for (int k = 0; k <= 7; ++k) {
            values.push_back(bounded(10 * power100));
            values.push_back(bounded(25 * power100));
            values.push_back(bounded(100 * power100 - rnd.next(0, 60)));
            values.push_back(bounded(250 * power100 + rnd.next(0, 60)));
            power100 *= 100;
        }
    } else if (mode == 3) {
        for (int i = 0; i < target; ++i) {
            values.push_back(randomChunkedPrice());
        }
    } else {
        values.push_back(1);
        values.push_back(9);
        values.push_back(10);
        values.push_back(24);
        values.push_back(25);
        values.push_back(47);
        values.push_back(99);
        values.push_back(1000000000000000LL);
        for (int i = 0; i < target; ++i) {
            long long base = rnd.any(values);
            long long multiplier = rnd.next(1, 1000);
            values.push_back(bounded(base + randomChunkedPrice() % multiplier));
        }
    }

    shuffle(values.begin(), values.end());

    int t = min<int>(values.size(), target);
    println(t);
    for (int i = 0; i < t; ++i) {
        println(values[i]);
    }

    return 0;
}
