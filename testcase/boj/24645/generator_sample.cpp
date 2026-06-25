#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const long long LIMIT = 1000000000000000000LL;

long long randomSmall() {
    return rnd.next(2LL, 200LL);
}

long long randomPowerOfTwo() {
    int exponent = rnd.next(1, 59);
    return 1LL << exponent;
}

long long randomPrimeLike() {
    static const vector<long long> primes = {
        2LL, 3LL, 5LL, 7LL, 11LL, 13LL, 17LL, 19LL, 97LL, 997LL,
        1000000007LL, 1000000009LL, 9999999967LL, 9999999973LL
    };
    return rnd.any(primes);
}

long long randomComposite() {
    long long a = rnd.next(2LL, 1000000LL);
    long long b = rnd.next(2LL, 1000000LL);
    return min(LIMIT, a * b);
}

long long randomNearLimit() {
    long long offset = rnd.next(0LL, 1000000LL);
    return LIMIT - offset;
}

long long randomCase() {
    int mode = rnd.next(0, 6);
    if (mode == 0) return randomSmall();
    if (mode == 1) return randomPowerOfTwo();
    if (mode == 2) return randomPrimeLike();
    if (mode == 3) return randomComposite();
    if (mode == 4) return randomNearLimit();
    if (mode == 5) return rnd.next(2LL, 1000000000000LL);
    return rnd.next(2LL, LIMIT);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 40);
    vector<long long> cases;
    cases.push_back(2);
    cases.push_back(3);
    cases.push_back(4);
    cases.push_back(6);
    cases.push_back(10);
    cases.push_back(LIMIT);
    cases.push_back(LIMIT - 1);

    while ((int)cases.size() < t) {
        cases.push_back(randomCase());
    }

    shuffle(cases.begin(), cases.end());
    println((int)cases.size());
    for (long long n : cases) {
        println(n);
    }

    return 0;
}
