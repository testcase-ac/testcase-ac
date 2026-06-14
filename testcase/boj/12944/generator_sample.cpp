#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int k;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 30);
        k = rnd.next(1, 6);
        for (int i = 0; i < k; ++i) {
            a.push_back(rnd.next(1, 30));
        }
    } else if (mode == 1) {
        n = rnd.next(50, 5000);
        k = rnd.next(5, 12);
        int base = rnd.next(2, 8);
        for (int i = 0; i < k; ++i) {
            int multiplier = rnd.next(1, 8);
            a.push_back(base * multiplier);
        }
    } else if (mode == 2) {
        n = rnd.next(100, 100000);
        k = rnd.next(8, 20);
        vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                              31, 37, 41, 43, 47, 53, 59, 61, 67, 71};
        shuffle(primes.begin(), primes.end());
        for (int i = 0; i < k; ++i) {
            a.push_back(primes[i]);
        }
    } else if (mode == 3) {
        n = rnd.next(1, 1000);
        k = rnd.next(4, 20);
        for (int i = 0; i < k; ++i) {
            if (rnd.next(0, 1) == 0) {
                a.push_back(rnd.next(1, n));
            } else {
                a.push_back(rnd.next(n + 1, 1000000000));
            }
        }
    } else if (mode == 4) {
        n = rnd.next(900000000, 1000000000);
        k = 20;
        for (int i = 0; i < k; ++i) {
            a.push_back(rnd.next(1, 1000000000));
        }
    } else {
        n = rnd.next(1, 1000000000);
        k = rnd.next(10, 20);
        int repeated = rnd.next(1, 1000);
        for (int i = 0; i < k; ++i) {
            if (rnd.next(0, 2) == 0) {
                a.push_back(repeated);
            } else {
                a.push_back(rnd.next(1, 1000000));
            }
        }
    }

    shuffle(a.begin(), a.end());
    println(n, k);
    println(a);

    return 0;
}
