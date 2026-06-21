#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_C = 1000000000;

int boundedPrimePower(int p) {
    int value = p;
    while (value <= MAX_C / p && rnd.next(2) == 0) value *= p;
    return value;
}

int smoothComposite(const vector<int>& primes) {
    int value = 1;
    int factors = rnd.next(2, 8);
    for (int i = 0; i < factors; ++i) {
        int p = rnd.any(primes);
        if (value > MAX_C / p) continue;
        value *= p;
    }
    return max(value, 2);
}

int productOfPowers(const vector<int>& primes) {
    int value = 1;
    int distinct = rnd.next(1, 4);
    vector<int> pool = primes;
    shuffle(pool.begin(), pool.end());

    for (int i = 0; i < distinct; ++i) {
        int p = pool[i];
        int term = boundedPrimePower(p);
        if (value <= MAX_C / term) value *= term;
    }
    return max(value, 2);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    vector<int> cases;

    int t = rnd.next(12, 40);
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(6);
        int c;

        if (mode == 0) {
            c = rnd.any(primes);
        } else if (mode == 1) {
            c = boundedPrimePower(rnd.any(primes));
        } else if (mode == 2) {
            c = smoothComposite(primes);
        } else if (mode == 3) {
            c = productOfPowers(primes);
        } else if (mode == 4) {
            c = MAX_C - rnd.next(0, 200);
        } else {
            c = rnd.next(2, MAX_C);
        }

        cases.push_back(c);
    }

    println((int)cases.size());
    for (int c : cases) println(c);

    return 0;
}
