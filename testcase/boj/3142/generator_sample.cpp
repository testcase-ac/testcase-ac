#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    vector<int> a;
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        int n = rnd.next(1, 40);
        int p = rnd.any(primes);
        for (int i = 0; i < n; ++i) {
            int x = p;
            if (rnd.next(0, 3) == 0) x *= p;
            a.push_back(x);
        }
    } else if (mode == 1) {
        int n = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) {
            int root = rnd.next(1, 1000);
            int x = root * root;
            if (rnd.next(0, 2) == 0) x = rnd.any(primes);
            a.push_back(x);
        }
    } else if (mode == 2) {
        int n = rnd.next(5, 70);
        for (int i = 0; i < n; ++i) {
            int x = 1;
            int factors = rnd.next(1, 6);
            for (int j = 0; j < factors; ++j) {
                int p = rnd.any(primes);
                if (x <= 1000000 / p) x *= p;
            }
            a.push_back(x);
        }
    } else if (mode == 3) {
        int n = rnd.next(5, 60);
        const vector<int> values = {1, 64, 729, 4096, 59049, 111111, 333333, 999999, 1000000};
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(values));
    } else {
        int n = rnd.next(10, 80);
        for (int i = 0; i < n; ++i) {
            int p = rnd.any(primes);
            if (rnd.next(0, 4) == 0) {
                int root = rnd.next(1, 1000);
                a.push_back(root * root);
            } else {
                a.push_back(p);
            }
        }
    }

    println(static_cast<int>(a.size()));
    for (int x : a) println(x);

    return 0;
}
