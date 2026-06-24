#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n;
long long k;
vector<long long> a;

struct Answer {
    string bits;
};

Answer readAnswer(InStream& stream) {
    string bits = stream.readToken("[01]+", "ciphertext bits");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after ciphertext bits");
    }

    if ((int)bits.size() != n) {
        stream.quitf(_wa, "ciphertext length is %d, expected %d", (int)bits.size(), n);
    }

    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        if (bits[i] == '1') {
            sum += a[i];
        }
    }
    if (sum != k) {
        stream.quitf(_wa, "ciphertext sum is %lld, expected %lld", sum, k);
    }

    return {bits};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readLong();
    }
    k = inf.readLong();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.bits == jury.bits) {
        quitf(_ok, "ciphertext matches jury answer");
    }
    quitf(_ok, "valid ciphertext differs from jury answer");
}
