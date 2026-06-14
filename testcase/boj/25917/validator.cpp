#include "testlib.h"

#include <vector>

using namespace std;

vector<bool> buildPrimeTable() {
    const int maxValue = 9999999;
    vector<bool> prime(maxValue + 1, true);
    prime[0] = false;
    prime[1] = false;

    for (int i = 2; i * i <= maxValue; ++i) {
        if (!prime[i]) {
            continue;
        }
        for (int j = i * i; j <= maxValue; j += i) {
            prime[j] = false;
        }
    }

    return prime;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const vector<bool> prime = buildPrimeTable();

    int r = inf.readInt(1, 500, "R");
    inf.readSpace();
    int c = inf.readInt(1, 500, "C");
    inf.readEoln();

    int n = r * c;
    vector<bool> seenPrime(prime.size(), false);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int value = inf.readInt(2, 9999999, "A_i");
        ensuref(prime[value], "A_%d must be prime, got %d", i + 1, value);
        ensuref(!seenPrime[value], "A_i values must be distinct, duplicate %d at index %d", value, i + 1);
        seenPrime[value] = true;
    }
    inf.readEoln();

    vector<bool> seenPosition(r + 1, false);
    for (int i = 0; i < r; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int position = inf.readInt(1, r, "P_i");
        ensuref(!seenPosition[position], "P must be a permutation, duplicate %d at index %d", position, i + 1);
        seenPosition[position] = true;
    }
    inf.readEoln();

    inf.readEof();
}
