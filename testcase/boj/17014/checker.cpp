#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int T = inf.readInt(1, 1000, "T");
    vector<int> n(T);
    int maxN = 0;
    for (int i = 0; i < T; ++i) {
        n[i] = inf.readInt(4, 1000000, format("N[%d]", i + 1).c_str());
        maxN = max(maxN, n[i]);
    }

    int limit = 2 * maxN;
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = false;
    isPrime[1] = false;
    for (long long p = 2; p * p <= limit; ++p) {
        if (!isPrime[p]) {
            continue;
        }
        for (long long q = p * p; q <= limit; q += p) {
            isPrime[q] = false;
        }
    }

    auto readAnswer = [&](InStream& stream) {
        for (int i = 0; i < T; ++i) {
            int a = stream.readInt(2, limit, format("A[%d]", i + 1).c_str());
            int b = stream.readInt(2, limit, format("B[%d]", i + 1).c_str());

            if (!isPrime[a]) {
                stream.quitf(_wa, "A[%d]=%d is not prime", i + 1, a);
            }
            if (!isPrime[b]) {
                stream.quitf(_wa, "B[%d]=%d is not prime", i + 1, b);
            }
            if (a + b != 2 * n[i]) {
                stream.quitf(_wa,
                             "case %d has A+B=%d, expected %d",
                             i + 1,
                             a + b,
                             2 * n[i]);
            }
        }
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after %d pairs", T);
        }
    };

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "all %d prime-pair certificates are valid", T);
}
