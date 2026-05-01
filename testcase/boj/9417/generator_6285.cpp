#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Precompute small primes up to 100
    vector<int> primes;
    vector<bool> isprime(201, true);
    isprime[0] = isprime[1] = false;
    for (int i = 2; i <= 200; i++) {
        if (isprime[i]) {
            if (i <= 100) primes.push_back(i);
            if (1LL * i * i <= 200)
                for (int j = i * i; j <= 200; j += i)
                    isprime[j] = false;
        }
    }

    int T = rnd.next(2, 7);
    println(T);
    for (int t = 0; t < T; t++) {
        int M;
        vector<int> a;
        if (t == 0) {
            // All-equal case
            M = rnd.next(2, 5);
            int x = rnd.next(1, 100);
            a.assign(M, x);
        } else {
            M = rnd.next(2, 12);
            int type = rnd.next(1, 3);
            if (type == 1) {
                // All primes (likely coprime)
                for (int i = 0; i < M; i++)
                    a.push_back(rnd.any(primes));
            } else if (type == 2) {
                // Heavy duplicates
                int x = rnd.next(1, 100);
                int dup = rnd.next(1, M - 1);
                for (int i = 0; i < dup; i++) a.push_back(x);
                for (int i = dup; i < M; i++) a.push_back(rnd.next(1, 100));
            } else {
                // Fully random
                for (int i = 0; i < M; i++)
                    a.push_back(rnd.next(1, 100));
            }
        }
        shuffle(a.begin(), a.end());
        println(a);
    }
    return 0;
}
