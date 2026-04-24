#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(5, 10);
    println(T);

    vector<long long> primes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
        31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
        73, 79, 83, 89, 97,
        100000007, 100000037, 999999937
    };

    for (int i = 0; i < T; i++) {
        int type = rnd.next(1, 6);
        long long N;
        switch (type) {
            case 1:
                // Small N
                N = rnd.next(1, 20);
                break;
            case 2: {
                // Power of two (often impossible)
                int e = rnd.next(0, 29);
                N = 1LL << e;
                break;
            }
            case 3: {
                // Odd N
                long long k = rnd.next(1, 500000);
                N = k * 2 + 1;
                break;
            }
            case 4:
                // Large random N
                N = rnd.next(100000000, 1000000000);
                break;
            case 5:
                // Prime N
                N = rnd.any(primes);
                break;
            case 6: {
                // N divisible by a small k
                int k = rnd.next(2, 10);
                int a = rnd.next(1, int(1000000000LL / k));
                N = 1LL * k * a;
                break;
            }
            default:
                N = rnd.next(1, 100);
        }
        println(N);
    }

    return 0;
}
