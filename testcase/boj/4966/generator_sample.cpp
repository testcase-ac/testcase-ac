#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

namespace {

constexpr int kMaxValue = 9999999;

void printDataset(const vector<int>& blue, const vector<int>& red) {
    println(static_cast<int>(blue.size()), static_cast<int>(red.size()));
    println(blue);
    println(red);
}

int pickPrimeFactor() {
    const vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    return rnd.any(primes);
}

int makeMultiple(int factor, int loMultiplier, int hiMultiplier) {
    return factor * rnd.next(loMultiplier, hiMultiplier);
}

void addSparseCoprimeDataset() {
    vector<int> blue;
    vector<int> red;
    vector<int> bluePrimes = {2, 3, 5, 7, 11, 13};
    vector<int> redPrimes = {17, 19, 23, 29, 31, 37};
    int m = rnd.next(1, 5);
    int n = rnd.next(1, 5);
    shuffle(bluePrimes.begin(), bluePrimes.end());
    shuffle(redPrimes.begin(), redPrimes.end());
    for (int i = 0; i < m; ++i) {
        blue.push_back(bluePrimes[i] * bluePrimes[i]);
    }
    for (int i = 0; i < n; ++i) {
        red.push_back(redPrimes[i] * redPrimes[i]);
    }
    printDataset(blue, red);
}

void addDenseDataset() {
    int factor = pickPrimeFactor();
    int m = rnd.next(2, 8);
    int n = rnd.next(2, 8);
    vector<int> blue(m), red(n);
    for (int& value : blue) {
        value = makeMultiple(factor, 1, 80);
    }
    for (int& value : red) {
        value = makeMultiple(factor, 1, 80);
    }
    printDataset(blue, red);
}

void addDuplicateDataset() {
    int shared = pickPrimeFactor() * rnd.next(1, 25);
    int offFactor = rnd.next(41, 97);
    int m = rnd.next(3, 9);
    int n = rnd.next(3, 9);
    vector<int> blue;
    vector<int> red;
    for (int i = 0; i < m; ++i) {
        blue.push_back(i % 3 == 0 ? shared : shared * rnd.next(1, 20));
    }
    for (int i = 0; i < n; ++i) {
        red.push_back(i % 2 == 0 ? shared : offFactor * rnd.next(1, 20));
    }
    shuffle(blue.begin(), blue.end());
    shuffle(red.begin(), red.end());
    printDataset(blue, red);
}

void addChainDataset() {
    int length = rnd.next(3, 7);
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19};
    shuffle(primes.begin(), primes.end());
    vector<int> blue;
    vector<int> red;
    for (int i = 0; i < length; ++i) {
        blue.push_back(primes[i] * primes[i + 1]);
        red.push_back(primes[i + 1] * primes[i + 1]);
    }
    if (rnd.next(2) == 0) {
        red.push_back(primes[0] * rnd.next(23, 41));
    }
    shuffle(blue.begin(), blue.end());
    shuffle(red.begin(), red.end());
    printDataset(blue, red);
}

void addBoundaryDataset() {
    vector<int> blue = {2, kMaxValue};
    vector<int> red = {rnd.next(2, 50) * 2, kMaxValue};
    if (rnd.next(2) == 0) {
        blue.push_back(9999991);
        red.push_back(9999991);
    }
    printDataset(blue, red);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasets = rnd.next(4, 9);
    for (int i = 0; i < datasets; ++i) {
        int mode = rnd.next(5);
        if (mode == 0) {
            addSparseCoprimeDataset();
        } else if (mode == 1) {
            addDenseDataset();
        } else if (mode == 2) {
            addDuplicateDataset();
        } else if (mode == 3) {
            addChainDataset();
        } else {
            addBoundaryDataset();
        }
    }

    println(0, 0);
    return 0;
}
