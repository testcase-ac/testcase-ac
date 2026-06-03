#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes;
    for (int x = 2; x <= 400; ++x) {
        bool prime = true;
        for (int d = 2; d * d <= x; ++d) {
            if (x % d == 0) {
                prime = false;
                break;
            }
        }
        if (prime) primes.push_back(x);
    }

    vector<int> products;
    for (int i = 0; i < (int)primes.size(); ++i) {
        for (int j = i + 1; j < (int)primes.size(); ++j) {
            int value = primes[i] * primes[j];
            if (value <= 100000) products.push_back(value);
        }
    }
    sort(products.begin(), products.end());

    int t = rnd.next(1, 20);
    vector<int> ks;
    ks.reserve(t);

    vector<int> fixed = {1, 2, 3, 4, 5, 6, 10, 300, 99991, 100000};
    shuffle(fixed.begin(), fixed.end());

    while ((int)ks.size() < t) {
        int mode = rnd.next(0, 6);
        int k;
        if (!fixed.empty() && mode <= 1) {
            k = fixed.back();
            fixed.pop_back();
        } else if (mode == 2) {
            k = rnd.next(1, 30);
        } else if (mode == 3) {
            k = rnd.next(99970, 100000);
        } else if (mode == 4) {
            int p = rnd.any(products);
            k = max(1, min(100000, p + rnd.next(-3, 3)));
        } else if (mode == 5) {
            int p = rnd.any(products);
            k = max(1, min(100000, p - rnd.next(0, 50)));
        } else {
            k = rnd.next(1, 100000);
        }
        ks.push_back(k);
    }

    println(t);
    for (int k : ks) println(k);

    return 0;
}
