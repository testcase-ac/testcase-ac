#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 8);
    println(t);

    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    vector<int> nearLimit = {840, 900, 960, 972, 980, 990, 1000};

    for (int tc = 0; tc < t; ++tc) {
        int mode = (tc < 3) ? tc : rnd.next(0, 5);
        vector<int> a;

        if (mode == 0) {
            a.push_back(rnd.next(1, 1000));
        } else if (mode == 1) {
            int base = rnd.any(vector<int>{2, 3, 5, 7, 10});
            int n = rnd.next(2, 10);
            int value = 1;
            for (int i = 0; i < rnd.next(1, 4); ++i) {
                if (value * base > 1000) break;
                value *= base;
            }
            for (int i = 0; i < n; ++i) {
                int x = value;
                if (rnd.next(0, 2) == 0) x = max(1, value / base);
                a.push_back(x);
            }
        } else if (mode == 2) {
            int n = rnd.next(3, 9);
            shuffle(primes.begin(), primes.end());
            for (int i = 0; i < n; ++i) {
                int x = primes[i % (int)primes.size()];
                if (rnd.next(0, 1) && x * primes[(i + 3) % (int)primes.size()] <= 1000) {
                    x *= primes[(i + 3) % (int)primes.size()];
                }
                a.push_back(x);
            }
        } else if (mode == 3) {
            int n = rnd.next(2, 7);
            for (int i = 0; i < n; ++i) a.push_back(rnd.any(nearLimit));
        } else {
            int n = rnd.next(5, 14);
            for (int i = 0; i < n; ++i) {
                if (rnd.next(0, 4) == 0) {
                    a.push_back(1);
                } else {
                    a.push_back(rnd.next(2, 60));
                }
            }
        }

        shuffle(a.begin(), a.end());
        println((int)a.size());
        println(a);
    }

    return 0;
}
