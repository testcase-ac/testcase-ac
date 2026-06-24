#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n;
vector<bool> isPrime;

struct Answer {
    bool hasWitness;
};

void buildPrimeTable() {
    int limit = n * (n + 1) / 2;
    isPrime.assign(limit + 1, true);
    if (limit >= 0) isPrime[0] = false;
    if (limit >= 1) isPrime[1] = false;
    for (int i = 2; i * i <= limit; ++i) {
        if (!isPrime[i]) continue;
        for (int j = i * i; j <= limit; j += i) {
            isPrime[j] = false;
        }
    }
}

Answer readAnswer(InStream& stream) {
    string verdict = stream.readToken("[A-Z]+", "verdict");

    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false};
    }

    if (verdict != "YES") {
        stream.quitf(_wa, "verdict must be YES or NO, found '%s'", verdict.c_str());
    }

    vector<bool> used(n + 1, false);
    int prefixSum = 0;
    for (int i = 1; i <= n; ++i) {
        int value = stream.readInt(1, n, format("permutation[%d]", i).c_str());
        if (used[value]) {
            stream.quitf(_wa, "value %d appears more than once", value);
        }
        used[value] = true;
        prefixSum += value;
        if (isPrime[prefixSum]) {
            stream.quitf(_wa, "prefix sum after day %d is prime: %d", i, prefixSum);
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after permutation");
    }
    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 5000, "N");
    buildPrimeTable();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.hasWitness == participant.hasWitness) {
        quitf(_ok, "%s", jury.hasWitness ? "valid permutation" : "both outputs are NO");
    }
    if (jury.hasWitness) {
        quitf(_wa, "jury has a valid permutation, but participant answered NO");
    }
    quitf(_fail, "participant found a valid permutation while jury answered NO");
}
