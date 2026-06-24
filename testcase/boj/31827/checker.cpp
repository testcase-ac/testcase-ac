#include "testlib.h"

#include <vector>

using namespace std;

const int MAX_A = 1000000;

int n, k;
vector<bool> isPrime;

void buildSieve() {
    isPrime.assign(MAX_A + 1, true);
    isPrime[0] = false;
    isPrime[1] = false;
    for (int p = 2; p * p <= MAX_A; ++p) {
        if (!isPrime[p]) {
            continue;
        }
        for (int q = p * p; q <= MAX_A; q += p) {
            isPrime[q] = false;
        }
    }
}

void readClaim(InStream& stream, TResult invalidVerdict, const char* who) {
    vector<int> a(n);
    vector<bool> used(MAX_A + 1, false);

    for (int i = 0; i < n; ++i) {
        a[i] = stream.readInt(2, MAX_A, format("%s[%d]", who, i + 1).c_str());
        if (!isPrime[a[i]]) {
            stream.quitf(invalidVerdict, "%s[%d]=%d is not prime", who, i + 1, a[i]);
        }
        if (used[a[i]]) {
            stream.quitf(invalidVerdict, "%s[%d]=%d is repeated", who, i + 1, a[i]);
        }
        used[a[i]] = true;
    }

    if (!stream.seekEof()) {
        stream.quitf(invalidVerdict, "extra output after %s sequence", who);
    }

    for (int start = 0; start + k <= n; ++start) {
        long long sum = 0;
        for (int offset = 0; offset < k; ++offset) {
            sum += a[start + offset];
        }
        if (sum % k != 0) {
            stream.quitf(invalidVerdict,
                         "%s subsequence starting at %d has sum %lld, not divisible by K=%d",
                         who,
                         start + 1,
                         sum,
                         k);
        }
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();

    buildSieve();

    readClaim(ans, _fail, "jury");
    readClaim(ouf, _wa, "participant");

    quitf(_ok, "valid prime sequence of length %d", n);
}
