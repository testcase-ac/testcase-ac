#include "testlib.h"

#include <vector>

using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;
    for (int d = 2; 1LL * d * d <= n; ++d) {
        if (n % d == 0) return false;
    }
    return true;
}

vector<int> primesInRange(int a, int b) {
    vector<int> primes;
    for (int x = a; x <= b; ++x) {
        if (isPrime(x)) primes.push_back(x);
    }
    return primes;
}

int randomKFromSubset(const vector<int>& primes) {
    if (primes.empty()) return rnd.next(1, 1000);

    vector<int> picked = primes;
    shuffle(picked.begin(), picked.end());

    long long sum = 0;
    int limit = rnd.next(1, min<int>(picked.size(), 6));
    for (int i = 0; i < limit && sum + picked[i] <= 2000000000LL; ++i) {
        if (rnd.next(0, 1) || sum == 0) sum += picked[i];
    }

    return max(1, int(sum));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int a;
    int b;
    int k;

    if (mode == 0) {
        a = rnd.next(1, 30);
        b = rnd.next(a + 1, min(50000000, a + rnd.next(1, 120)));
        k = rnd.next(1, 300);
    } else if (mode == 1) {
        a = 8 + 2 * rnd.next(0, 20);
        b = a + rnd.next(1, 2);
        k = rnd.next(1, 200);
    } else if (mode == 2) {
        a = rnd.next(1, 20000);
        b = a + rnd.next(1, 300);
        k = rnd.next(1, 200000);
    } else if (mode == 3) {
        b = rnd.next(49999700, 50000000);
        a = rnd.next(max(1, b - 300), b - 1);
        k = rnd.next(1, 2000000000);
    } else if (mode == 4) {
        a = rnd.next(1, 50000000 - 1);
        b = a + rnd.next(1, min(12, 50000000 - a));
        k = rnd.next(1, 1000000);
    } else if (mode == 5) {
        a = rnd.next(1, 5000);
        b = a + rnd.next(1, 300);
        k = randomKFromSubset(primesInRange(a, b));
    } else {
        a = rnd.next(1, 50000000 - 300);
        b = a + rnd.next(1, 300);
        k = rnd.next(1500000000, 2000000000);
    }

    println(a, b, k);
    return 0;
}
