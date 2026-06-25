#include "testlib.h"
#include <vector>
using namespace std;

bool isPrime(int x) {
    if (x < 2) return false;
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes;
    for (int x = 2; x <= 211; ++x) {
        if (isPrime(x)) primes.push_back(x);
    }

    int mode = rnd.next(0, 5);
    int index = 0;
    if (mode == 0) {
        index = rnd.next(0, min<int>(8, primes.size() - 1));
    } else if (mode == 1) {
        index = rnd.next(max<int>(0, (int)primes.size() - 10), (int)primes.size() - 1);
    } else if (mode == 2) {
        index = rnd.next((int)primes.size() / 3, 2 * (int)primes.size() / 3);
    } else if (mode == 3) {
        index = rnd.wnext((int)primes.size(), 2);
    } else if (mode == 4) {
        index = rnd.wnext((int)primes.size(), -2);
    } else {
        index = rnd.next((int)primes.size());
    }

    println(primes[index]);
    return 0;
}
