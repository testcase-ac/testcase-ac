#include "testlib.h"
using namespace std;

bool isPrime(int x) {
    if (x < 2) return false;
    for (int i = 2; (long long)i * i <= x; ++i)
        if (x % i == 0) return false;
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 5);

    int n;
    int a, b;
    vector<int> r1, r2;

    // Choose relation between a and b: sometimes a>b, sometimes a<b, sometimes equal
    int abCase = rnd.next(0, 9);
    if (abCase <= 3) { // 40%: a > b
        a = rnd.next(2, 10);
        b = rnd.next(1, a - 1);
    } else if (abCase <= 6) { // 30%: a < b
        b = rnd.next(2, 10);
        a = rnd.next(1, b - 1);
    } else { // 30%: a == b
        a = b = rnd.next(1, 10);
    }

    switch (scenario) {
        case 0: {
            // Completely random small instance
            n = rnd.next(1, 15);
            r1.resize(n);
            r2.resize(n);
            for (int i = 0; i < n; ++i) {
                r1[i] = rnd.next(1, 30);
                r2[i] = rnd.next(1, 30);
            }
            break;
        }
        case 1: {
            // n = 1 edge case
            n = 1;
            r1.resize(1);
            r2.resize(1);
            r1[0] = rnd.next(1, 30);
            r2[0] = rnd.next(1, 30);
            break;
        }
        case 2: {
            // Vertical sums always prime, horizontal always composite
            // Use pattern: top = 1, bottom = 2 -> vertical sum = 3 (prime)
            // horizontals: 1+1=2 (prime) and 2+2=4 (composite), but horizontals
            // involve adjacent columns, so sums: 1+1=2 (prime!) and 2+2=4.
            // To avoid horizontal primes, use different pattern:
            // top =1, bottom=4 => vertical=5 (prime),
            // horizontals top:1+1=2 (prime) again, so still primes.
            // Instead, use: top=2, bottom=3: vertical=5 (prime),
            // horizontals: 2+2=4 (composite), 3+3=6 (composite).
            n = 2 * rnd.next(1, 10); // even n between 2 and 20
            r1.assign(n, 2);
            r2.assign(n, 3);
            break;
        }
        case 3: {
            // All sums composite: any domino (vertical or horizontal) gives composite sum
            // Use: row1 all 4, row2 all 6
            n = rnd.next(2, 20);
            r1.assign(n, 4);
            r2.assign(n, 6);
            break;
        }
        case 4: {
            // Alternating prime / composite vertical sums to force mixed decisions
            n = rnd.next(5, 12);
            r1.assign(n, 0);
            r2.assign(n, 0);
            bool startPrime = rnd.next(0, 1) == 1;
            for (int i = 0; i < n; ++i) {
                bool wantPrime = (i % 2 == 0 ? startPrime : !startPrime);
                while (true) {
                    int top = rnd.next(1, 40);
                    int bottom = rnd.next(1, 40);
                    bool vPrime = isPrime(top + bottom);
                    if (vPrime == wantPrime) {
                        r1[i] = top;
                        r2[i] = bottom;
                        break;
                    }
                }
            }
            break;
        }
        case 5: {
            // Larger instance with structured blocks and randomness
            n = rnd.next(20, 40);
            r1.assign(n, 0);
            r2.assign(n, 0);
            int i = 0;
            while (i < n) {
                int remaining = n - i;
                int pat = rnd.next(0, 2);
                if (remaining >= 2 && pat == 2) pat = rnd.next(0, 1); // avoid 2 when <2 left

                if (pat == 0) {
                    // Single column with prime vertical sum
                    bool wantPrime = true;
                    while (true) {
                        int top = rnd.next(1, 40);
                        int bottom = rnd.next(1, 40);
                        if (isPrime(top + bottom) == wantPrime) {
                            r1[i] = top;
                            r2[i] = bottom;
                            break;
                        }
                    }
                    ++i;
                } else if (pat == 1) {
                    // Single column with composite vertical sum
                    bool wantPrime = false;
                    while (true) {
                        int top = rnd.next(1, 40);
                        int bottom = rnd.next(1, 40);
                        if (isPrime(top + bottom) == wantPrime) {
                            r1[i] = top;
                            r2[i] = bottom;
                            break;
                        }
                    }
                    ++i;
                } else {
                    // 2-column block with strong vertical vs horizontal contrast
                    if (remaining < 2) {
                        // fallback to random if only one left
                        r1[i] = rnd.next(1, 40);
                        r2[i] = rnd.next(1, 40);
                        ++i;
                    } else {
                        // pattern: [2,2] on top, [3,3] on bottom
                        r1[i] = 2; r2[i] = 3;
                        r1[i+1] = 2; r2[i+1] = 3;
                        i += 2;
                    }
                }
            }
            break;
        }
    }

    // Output
    println(n, a, b);
    println(r1);
    println(r2);

    return 0;
}
