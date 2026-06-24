#include "testlib.h"

#include <vector>

using namespace std;

int n;
vector<bool> isPrime;

struct Answer {
    bool impossible;
    vector<int> primes;
};

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, n, "answer[1]");

    if (first == -1) {
        stream.readEoln();
        stream.readEof();
        if (n >= 8) {
            stream.quitf(_wa, "-1 is invalid because %d can be written as four primes", n);
        }
        return {true, {}};
    }

    vector<int> p(4);
    p[0] = first;
    if (p[0] < 2) {
        stream.quitf(_wa, "answer[1]=%d is not prime", p[0]);
    }
    for (int i = 1; i < 4; ++i) {
        p[i] = stream.readInt(2, n, format("answer[%d]", i + 1).c_str());
    }
    stream.readEoln();
    stream.readEof();

    long long sum = 0;
    for (int i = 0; i < 4; ++i) {
        if (!isPrime[p[i]]) {
            stream.quitf(_wa, "answer[%d]=%d is not prime", i + 1, p[i]);
        }
        sum += p[i];
    }
    if (sum != n) {
        stream.quitf(_wa, "prime sum is %lld instead of %d", sum, n);
    }

    return {false, p};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 1000000, "N");

    isPrime.assign(n + 1, true);
    if (n >= 0) isPrime[0] = false;
    if (n >= 1) isPrime[1] = false;
    for (long long i = 2; i * i <= n; ++i) {
        if (!isPrime[i]) continue;
        for (long long j = i * i; j <= n; j += i) {
            isPrime[j] = false;
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.impossible && !jury.impossible) {
        quitf(_wa, "participant reported impossible but jury has a valid decomposition");
    }
    if (!participant.impossible && jury.impossible) {
        quitf(_fail, "participant found a valid decomposition but jury reported impossible");
    }

    quitf(_ok, "valid output");
}
