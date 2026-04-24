#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int t = rnd.next(1, 10);
    println(t);
    // A small list of primes for one type of test
    vector<int> primes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
    for (int tc = 0; tc < t; tc++) {
        // Number count
        int n = rnd.next(2, 10);
        // Test type: 0 = random, 1 = multiples, 2 = primes
        int type = rnd.next(0, 2);
        vector<int> a(n);
        if (type == 0) {
            // random numbers in [1,1000]
            for (int i = 0; i < n; i++)
                a[i] = rnd.next(1, 1000);
        } else if (type == 1) {
            // multiples of a base
            int base = rnd.next(1, 100);
            for (int i = 0; i < n; i++)
                a[i] = base * rnd.next(1, 10);
        } else {
            // random small primes
            for (int i = 0; i < n; i++)
                a[i] = rnd.any(primes);
        }
        // Introduce some duplicates with ~30% probability
        if (rnd.next() < 0.3) {
            for (int i = 1; i < n; i++) {
                if (rnd.next(0,1) == 0) {
                    int j = rnd.next(0, i-1);
                    a[i] = a[j];
                }
            }
        }
        // Shuffle order
        shuffle(a.begin(), a.end());
        // Output this test case
        printf("%d", n);
        for (int x : a) printf(" %d", x);
        printf("\n");
    }
    return 0;
}
