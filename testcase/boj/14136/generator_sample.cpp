#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> primes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
        31, 37, 41, 43, 47, 53, 59, 61, 67, 71
    };

    vector<int> a;
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        int x = rnd.next(1, 12);
        int len = rnd.next(6, 18);
        for (int i = 0; i < len; ++i) {
            a.push_back(x);
            int mul = rnd.any(vector<int>{2, 2, 3, 4, 5});
            if (x <= 999999 / mul) {
                x *= mul;
            }
        }
    } else if (mode == 1) {
        int base = rnd.next(1, 40);
        int n = rnd.next(12, 30);
        for (int i = 0; i < n; ++i) {
            int mul = rnd.next(1, 12);
            a.push_back(base * mul);
        }
    } else if (mode == 2) {
        int n = rnd.next(10, 25);
        vector<int> pool = primes;
        shuffle(pool.begin(), pool.end());
        for (int i = 0; i < n; ++i) {
            int p = pool[i % (int)pool.size()];
            int value = p * rnd.next(1, 999999 / p);
            if (rnd.next(0, 3) == 0) {
                value = p;
            }
            a.push_back(value);
        }
    } else if (mode == 3) {
        int chains = rnd.next(2, 5);
        for (int c = 0; c < chains; ++c) {
            int x = rnd.next(1, 30);
            int len = rnd.next(3, 7);
            for (int i = 0; i < len; ++i) {
                a.push_back(x);
                int mul = rnd.next(2, 6);
                if (x <= 999999 / mul) {
                    x *= mul;
                }
            }
        }
        shuffle(a.begin(), a.end());
    } else {
        int n = rnd.next(8, 22);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                a.push_back(999999 - rnd.next(0, 200));
            } else if (i % 3 == 1) {
                a.push_back(rnd.next(1, 100));
            } else {
                int x = rnd.next(1000, 9999);
                a.push_back(x * rnd.next(1, 999999 / x));
            }
        }
    }

    if (rnd.next(0, 5) == 0) {
        a.insert(a.begin(), 1);
    }

    println((int)a.size());
    for (int x : a) {
        println(x);
    }

    return 0;
}
