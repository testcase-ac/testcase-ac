#include "testlib.h"
#include <vector>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIM = (long long)1e12;
    const int MAXP = 1000000;
    vector<bool> isPrime(MAXP+1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * (long long)i <= MAXP; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= MAXP; j += i)
                isPrime[j] = false;
        }
    }
    vector<int> primes;
    for (int i = 2; i <= MAXP; i++) if (isPrime[i]) primes.push_back(i);
    // small primes <=100
    vector<int> primesSmall;
    for (int p : primes) if (p <= 100) primesSmall.push_back(p);
    // large primes >1000
    vector<int> primesLarge;
    for (int p : primes) if (p > 1000) primesLarge.push_back(p);
    // composite numbers <=1000
    vector<int> compositesSmall;
    for (int i = 4; i <= 1000; i++) if (!isPrime[i]) compositesSmall.push_back(i);
    // composite numbers <=50
    vector<int> compositesTiny;
    for (int i = 4; i <= 50; i++) if (!isPrime[i]) compositesTiny.push_back(i);

    // choose category
    int cat = rnd.next(0, 6);
    long long N = -1;
    if (cat == 0) {
        // small prime
        N = rnd.any(primesSmall);
    } else if (cat == 1) {
        // small composite trivial: 2 * small prime>2
        vector<int> ps;
        for (int p : primesSmall) if (p > 2) ps.push_back(p);
        int p = rnd.any(ps);
        N = 2LL * p;
    } else if (cat == 2) {
        // semiprime large
        int p = rnd.any(primesLarge);
        int q = rnd.any(primesLarge);
        N = (long long)p * q;
    } else if (cat == 3) {
        // prime square
        int p = rnd.any(primes);
        N = (long long)p * p;
    } else if (cat == 4) {
        // prime power p^e, e>=4
        vector<int> base = {2,3,5,7,11};
        int p = rnd.any(base);
        int e = rnd.next(4, 6);
        long long v = 1;
        for (int i = 0; i < e; i++) v *= p;
        N = v;
    } else if (cat == 5) {
        // product of two composites
        int c1 = rnd.any(compositesSmall);
        int c2 = rnd.any(compositesSmall);
        N = (long long)c1 * c2;
    } else {
        // product of 3 or 4 composites
        int len = rnd.next(3, 4);
        long long v = 1;
        for (int i = 0; i < len; i++) {
            int c = rnd.any(compositesTiny);
            v *= c;
        }
        N = v;
    }
    // safety clamp
    if (N < 2) N = 2;
    if (N > LIM) N = LIM;

    println(N);
    return 0;
}
