#include "testlib.h"

#include <vector>

using namespace std;

int k;
vector<int> primes;
vector<vector<int>> factorialParity;

struct Answer {
    vector<int> removed;
};

void buildFactorialParity() {
    vector<int> isComposite(k + 1, 0);
    for (int i = 2; i <= k; ++i) {
        if (!isComposite[i]) {
            primes.push_back(i);
            if (1LL * i * i <= k) {
                for (long long j = 1LL * i * i; j <= k; j += i) {
                    isComposite[(int)j] = 1;
                }
            }
        }
    }

    factorialParity.assign(k + 1, vector<int>(primes.size(), 0));
    for (int i = 1; i <= k; ++i) {
        factorialParity[i] = factorialParity[i - 1];
        int value = i;
        for (int pi = 0; pi < (int)primes.size(); ++pi) {
            int prime = primes[pi];
            while (value % prime == 0) {
                factorialParity[i][pi] ^= 1;
                value /= prime;
            }
            if (value == 1) {
                break;
            }
        }
    }
}

Answer readAnswer(InStream& stream) {
    vector<int> removed;
    int previous = 0;

    while (!stream.seekEof()) {
        int index = stream.readInt(1, k, format("removed[%d]", (int)removed.size() + 1).c_str());
        if (index <= previous) {
            stream.quitf(_wa, "removed indices must be strictly increasing, found %d after %d",
                         index, previous);
        }
        removed.push_back(index);
        previous = index;
    }

    if (removed.empty()) {
        stream.quitf(_wa, "at least one factorial index must be printed");
    }

    vector<int> parity(primes.size(), 0);
    for (int i = 1; i <= k; ++i) {
        for (int pi = 0; pi < (int)primes.size(); ++pi) {
            parity[pi] ^= factorialParity[i][pi];
        }
    }
    for (int index : removed) {
        for (int pi = 0; pi < (int)primes.size(); ++pi) {
            parity[pi] ^= factorialParity[index][pi];
        }
    }

    for (int pi = 0; pi < (int)primes.size(); ++pi) {
        if (parity[pi]) {
            stream.quitf(_wa, "remaining product is not a square; prime %d has odd exponent",
                         primes[pi]);
        }
    }

    return {removed};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    k = inf.readInt(2, 500, "k");
    inf.seekEof();
    buildFactorialParity();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.removed.size() < jury.removed.size()) {
        quitf(_fail, "participant found a valid smaller answer: jury=%d participant=%d",
              (int)jury.removed.size(), (int)participant.removed.size());
    }
    if (participant.removed.size() > jury.removed.size()) {
        quitf(_wa, "jury has a smaller answer: jury=%d participant=%d",
              (int)jury.removed.size(), (int)participant.removed.size());
    }

    quitf(_ok, "valid answer with %d removed factorials", (int)participant.removed.size());
}
