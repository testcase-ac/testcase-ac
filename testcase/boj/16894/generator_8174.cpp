#include "testlib.h"
#include <vector>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<ll> smallPrimes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
    vector<ll> smallComps;
    for (int i = 4; i <= 100; i++) {
        bool isComposite = false;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) { isComposite = true; break; }
        }
        if (isComposite) smallComps.push_back(i);
    }
    vector<ll> primesForPower = {2,3,5,7,11,13,17,19,23,29};
    vector<ll> bigPrimes = {999999937LL, 999999929LL, 999999893LL, 999999883LL, 9999999967LL};

    int mode = rnd.next(0, 6);
    ll N = 1;
    if (mode == 0) {
        N = 1;
    } else if (mode == 1) {
        N = rnd.any(smallPrimes);
    } else if (mode == 2) {
        N = rnd.any(smallComps);
    } else if (mode == 3) {
        N = rnd.next(1000LL, 10000LL);
    } else if (mode == 4) {
        ll p = rnd.any(primesForPower);
        ll tmp = 1;
        int expMax = 0;
        while (tmp * p <= 10000000000000LL) {
            tmp *= p;
            expMax++;
        }
        int e = rnd.next(2, max(2, expMax));
        ll val = 1;
        for (int i = 0; i < e; i++) val *= p;
        N = val;
    } else if (mode == 5) {
        int limit = 1000000;
        vector<char> sieve(limit+1, true);
        sieve[0] = sieve[1] = false;
        vector<int> primes;
        for (int i = 2; i <= limit; i++) {
            if (sieve[i]) {
                primes.push_back(i);
                if ((ll)i * i <= limit)
                    for (int j = i * i; j <= limit; j += i)
                        sieve[j] = false;
            }
        }
        int a = rnd.next(0, (int)primes.size() - 1);
        int b = rnd.next(0, (int)primes.size() - 1);
        ll prod = (ll)primes[a] * primes[b];
        N = prod;
    } else {
        N = rnd.any(bigPrimes);
    }

    println(N);
    return 0;
}
