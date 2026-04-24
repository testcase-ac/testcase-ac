#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a generation type for diversity
    int type = rnd.next(0, 5);
    int n;

    if (type == 0) {
        // small n
        n = rnd.next(1, 10);
    } else if (type == 1) {
        // medium n
        n = rnd.next(11, 100);
    } else if (type == 2) {
        // large random n
        n = rnd.next(101, 10000);
    } else if (type == 3) {
        // prime n
        const int MAXN = 10000;
        vector<bool> isprime(MAXN+1, true);
        isprime[0] = isprime[1] = false;
        vector<int> primes;
        for (int i = 2; i <= MAXN; ++i) {
            if (isprime[i]) {
                primes.push_back(i);
                if ((long long)i * i <= MAXN) {
                    for (int j = i * i; j <= MAXN; j += i)
                        isprime[j] = false;
                }
            }
        }
        n = rnd.any(primes);
    } else if (type == 4) {
        // perfect square
        int k = rnd.next(1, 100);
        n = k * k;
    } else {
        // highly composite under 10000
        vector<int> hc = {60, 360, 840, 1260, 1680, 2520, 5040, 7560};
        n = rnd.any(hc);
    }

    println(n);
    return 0;
}
