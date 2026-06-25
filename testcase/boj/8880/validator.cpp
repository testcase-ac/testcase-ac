#include "testlib.h"

#include <cstring>

using namespace std;

const long long LIMIT = 9223372036854775807LL;
const int PRIMES[20] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                        31, 37, 41, 43, 47, 53, 59, 61, 67, 71};

long long target;
bool found;
int exponentCount[20];
int totalFactors;
__int128 arrangements;
__int128 product;

void search(int primeIndex) {
    if (arrangements > target || product > LIMIT) {
        return;
    }
    if (arrangements == target) {
        found = true;
        return;
    }

    if (product * PRIMES[primeIndex] <= LIMIT &&
        (primeIndex == 0 || exponentCount[primeIndex - 1] > exponentCount[primeIndex])) {
        exponentCount[primeIndex]++;
        product *= PRIMES[primeIndex];
        totalFactors++;
        arrangements *= totalFactors;
        arrangements /= exponentCount[primeIndex];

        search(primeIndex);

        arrangements *= exponentCount[primeIndex];
        arrangements /= totalFactors;
        totalFactors--;
        product /= PRIMES[primeIndex];
        exponentCount[primeIndex]--;
    }

    if (primeIndex + 1 < 20 && product * PRIMES[primeIndex + 1] <= LIMIT) {
        exponentCount[primeIndex + 1]++;
        product *= PRIMES[primeIndex + 1];
        totalFactors++;
        arrangements *= totalFactors;
        arrangements /= exponentCount[primeIndex + 1];

        search(primeIndex + 1);

        arrangements *= exponentCount[primeIndex + 1];
        arrangements /= totalFactors;
        totalFactors--;
        product /= PRIMES[primeIndex + 1];
        exponentCount[primeIndex + 1]--;
    }
}

bool hasAnswerBelowLimit(long long n) {
    memset(exponentCount, 0, sizeof(exponentCount));
    target = n;
    found = false;
    totalFactors = 1;
    arrangements = 1;
    product = 2;
    exponentCount[0] = 1;

    search(0);
    return found;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCases = 0;
    while (!inf.eof()) {
        testCases++;
        ensuref(testCases <= 1000, "too many test cases: %d", testCases);
        setTestCase(testCases);

        long long n = inf.readLong(1LL, LIMIT, "n");
        inf.readEoln();

        ensuref(hasAnswerBelowLimit(n), "no k < 2^63 exists for n=%lld", n);
    }

    ensuref(testCases >= 1, "at least one test case is required");
    inf.readEof();
}
