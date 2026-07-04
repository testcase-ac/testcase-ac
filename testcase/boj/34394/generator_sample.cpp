#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long LIMIT = 1000000000000000LL;

long long chooseT(int mode, long long product) {
    if (mode == 0) {
        return rnd.next(1LL, 200LL);
    }
    if (mode == 1) {
        return rnd.next(1LL, min(1000000LL, product * rnd.next(1LL, 20LL)));
    }
    if (mode == 2) {
        return max(1LL, product - rnd.next(0LL, min(product - 1, 1000LL)));
    }
    if (mode == 3) {
        return min(LIMIT, product + rnd.next(0LL, min(LIMIT - product, 1000000LL)));
    }
    return rnd.next(LIMIT - 1000000LL, LIMIT);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> small = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    vector<long long> medium = {
        31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97
    };
    vector<long long> large = {
        999983, 1000003, 1000033, 1000037, 1000039, 1000081,
        1000099, 1000117, 1000121, 1000133, 1000151, 1000159
    };

    int mode = rnd.next(0, 4);
    vector<long long> pool;
    if (mode == 0) {
        pool = small;
    } else if (mode == 1) {
        pool = small;
        pool.insert(pool.end(), medium.begin(), medium.end());
    } else if (mode == 2) {
        pool = medium;
    } else {
        pool = large;
        pool.insert(pool.end(), small.begin(), small.end());
    }

    shuffle(pool.begin(), pool.end());

    int targetN = 1;
    if (mode == 0) {
        targetN = rnd.next(1, 4);
    } else if (mode == 1) {
        targetN = rnd.next(6, 10);
    } else if (mode == 2) {
        targetN = rnd.next(3, 8);
    } else {
        targetN = rnd.next(2, 5);
    }

    vector<long long> cycles;
    long long product = 1;
    for (long long p : pool) {
        if ((int)cycles.size() == targetN) {
            break;
        }
        if (product <= LIMIT / p) {
            cycles.push_back(p);
            product *= p;
        }
    }

    if (cycles.empty()) {
        cycles.push_back(2);
        product = 2;
    }

    shuffle(cycles.begin(), cycles.end());
    long long t = chooseT(mode, product);

    println((int)cycles.size(), t);
    for (long long c : cycles) {
        println(c);
    }

    return 0;
}
