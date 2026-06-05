#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int targetExp;
    int maxNonZero;

    if (mode == 0) {
        targetExp = rnd.next(0, 8);
        maxNonZero = rnd.next(1, 12);
    } else if (mode == 1) {
        targetExp = rnd.next(9, 30);
        maxNonZero = rnd.next(2, 18);
    } else if (mode == 2) {
        targetExp = rnd.next(55, 62);
        maxNonZero = rnd.next(1, 10);
    } else {
        targetExp = rnd.next(0, 62);
        maxNonZero = rnd.next(8, 28);
    }

    vector<int> exponents(1, targetExp);
    int splitAttempts = rnd.next(maxNonZero * 2, maxNonZero * 5);
    for (int attempt = 0; attempt < splitAttempts && (int)exponents.size() < maxNonZero; ++attempt) {
        vector<int> splittable;
        for (int i = 0; i < (int)exponents.size(); ++i) {
            if (exponents[i] > 0) {
                splittable.push_back(i);
            }
        }
        if (splittable.empty()) {
            break;
        }

        int idx = rnd.any(splittable);
        int nextExp = exponents[idx] - 1;
        exponents[idx] = nextExp;
        exponents.push_back(nextExp);
    }

    if (mode == 4 && targetExp < 62 && (int)exponents.size() + 1 <= maxNonZero) {
        exponents.push_back(rnd.next(0, targetExp));
    }

    int zeroCount;
    if (mode == 3) {
        zeroCount = rnd.next((int)exponents.size(), (int)exponents.size() * 3 + 5);
    } else {
        zeroCount = rnd.next(0, 12);
    }

    vector<long long> values;
    for (int exponent : exponents) {
        values.push_back(1LL << exponent);
    }
    values.insert(values.end(), zeroCount, 0LL);
    shuffle(values.begin(), values.end());

    println((int)values.size());
    println(values);

    return 0;
}
