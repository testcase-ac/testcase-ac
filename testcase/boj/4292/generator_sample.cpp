#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxP = 100000;
    vector<bool> isPrime(maxP + 1, true);
    isPrime[0] = false;
    isPrime[1] = false;
    for (int i = 2; i * i <= maxP; ++i) {
        if (!isPrime[i]) continue;
        for (int j = i * i; j <= maxP; j += i) {
            isPrime[j] = false;
        }
    }

    vector<int> small;
    vector<int> medium;
    vector<int> large;
    for (int p = 2; p <= maxP; ++p) {
        if (!isPrime[p]) continue;
        if (p <= 97) {
            small.push_back(p);
        } else if (p <= 2000) {
            medium.push_back(p);
        } else {
            large.push_back(p);
        }
    }

    int mode = rnd.next(0, 3);
    vector<int> values;
    int sum = 0;

    auto addPrime = [&](int p) {
        if (sum + p <= maxP) {
            values.push_back(p);
            sum += p;
        }
    };

    if (mode == 0) {
        int count = rnd.next(1, 12);
        for (int i = 0; i < count; ++i) {
            addPrime(rnd.any(small));
        }
    } else if (mode == 1) {
        int count = rnd.next(2, 8);
        for (int i = 0; i < count; ++i) {
            addPrime(i == 0 ? rnd.any(small) : rnd.any(medium));
        }
    } else if (mode == 2) {
        int count = rnd.next(1, 4);
        for (int i = 0; i < count; ++i) {
            addPrime(rnd.any(large));
        }
        int filler = rnd.next(0, 5);
        for (int i = 0; i < filler; ++i) {
            addPrime(rnd.any(small));
        }
    } else {
        addPrime(2);
        int count = rnd.next(1, 9);
        for (int i = 0; i < count; ++i) {
            addPrime(rnd.any(i % 2 == 0 ? small : medium));
        }
    }

    if (values.empty()) {
        addPrime(2);
    }

    shuffle(values.begin(), values.end());
    for (int p : values) {
        println(p);
    }
    println(0);

    return 0;
}
