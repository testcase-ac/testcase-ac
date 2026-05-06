#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: N (1 ≤ N ≤ 10^18)
    long long N = inf.readLong(1LL, (long long)1e18, "N");
    inf.readEoln();

    /*
        Problem guarantee:
        "주어지는 N은 소인수가 모두 100,000 이하인 수이다."
        = All prime factors of N are ≤ 100000.

        We must *validate* this.

        Correct logic:
        Repeatedly factor out all prime factors ≤ 100000.
        If something > 1 remains, that remainder itself must be a prime > 100000
        (or product of such primes), which is forbidden.

        The previous failed attempt only trial-divided up to sqrt(current x) OR 100000,
        whichever was smaller, which stopped too early for cases where the remaining
        factor is a prime ≤ 100000 but larger than sqrt(original N). E.g., N=86=2*43:
        after dividing by 2, x=43; the loop condition p*p<=x prevents p=43 from being
        tested, so 43 remains and validator incorrectly concludes it is >100000.

        Fix: we must try all p from 2 to 100000 (or up to current x, whichever is smaller),
        without the p*p <= x stop condition, because we are not trying to *test primality*;
        we just need to remove all factors ≤ 100000 from N.
    */

    const long long LIM = 100000LL;
    long long x = N;

    // Factor out all prime factors ≤ 100000 by trial division.
    // Complexity: at most 100000 iterations, fine.
    for (long long p = 2; p <= LIM && p <= x; ++p) {
        if (x % p == 0) {
            do {
                x /= p;
            } while (x % p == 0);
        }
    }

    // After removing all factors ≤ 100000, the remaining part (if >1)
    // must *not* exist according to the statement.
    ensuref(
        x == 1LL,
        "N has a prime factor greater than 100000 (remaining factor after removing all <=100000 is %lld)",
        x
    );

    inf.readEof();
}
