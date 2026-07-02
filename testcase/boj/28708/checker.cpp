#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static int n;
static vector<int> a;
static vector<bool> isPrime;

struct Answer {
    int k;
};

static void buildSieve(int limit) {
    isPrime.assign(limit + 1, true);
    if (limit >= 0) isPrime[0] = false;
    if (limit >= 1) isPrime[1] = false;
    for (int i = 2; 1LL * i * i <= limit; ++i) {
        if (!isPrime[i]) continue;
        for (int j = i * i; j <= limit; j += i) {
            isPrime[j] = false;
        }
    }
}

static Answer readAnswer(InStream& stream) {
    int k = stream.readInt(0, n, "K");
    vector<int> changed(n, 0);

    for (int i = 0; i < k; ++i) {
        int index = stream.readInt(1, n, format("index[%d]", i + 1).c_str());
        if (changed[index - 1]) {
            stream.quitf(_wa, "index %d is repeated", index);
        }
        changed[index - 1] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after operation indices");
    }

    vector<int> b = a;
    for (int i = 0; i < n; ++i) {
        b[i] += changed[i];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int sum = b[i] + b[j];
            if (isPrime[sum]) {
                stream.quitf(_wa,
                             "A[%d]+A[%d]=%d is prime after the operation",
                             i + 1,
                             j + 1,
                             sum);
            }
        }
    }

    return {k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    a.resize(n);
    int maxA = 0;
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readInt();
        maxA = max(maxA, a[i]);
    }

    buildSieve(2 * maxA + 2);

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.k < jury.k) {
        quitf(_fail,
              "participant found a better valid operation: jury K=%d, participant K=%d",
              jury.k,
              participant.k);
    }
    if (participant.k > jury.k) {
        quitf(_wa,
              "participant K=%d is worse than jury K=%d",
              participant.k,
              jury.k);
    }

    quitf(_ok, "valid operation with K=%d", participant.k);
}
