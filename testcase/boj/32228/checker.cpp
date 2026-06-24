#include "testlib.h"

#include <vector>
using namespace std;

int n;
long long m;
vector<long long> a;

long long modPow(long long base, long long exp) {
    long long result = 1 % m;
    base %= m;
    while (exp > 0) {
        if (exp & 1) {
            result = static_cast<long long>((__int128)result * base % m);
        }
        base = static_cast<long long>((__int128)base * base % m);
        exp >>= 1;
    }
    return result;
}

struct Answer {
    bool impossible;
    long long k;
};

Answer readAnswer(InStream& stream) {
    long long value = stream.readLong(-1, m, "answer");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }

    if (value == -1) {
        return {true, -1};
    }
    if (value == 0) {
        stream.quitf(_wa, "K must be -1 or in [1, %lld]", m);
    }

    long long first = modPow(a[0], value);
    long long second = modPow(a[1], value);
    long long diff = (second - first + m) % m;
    long long previous = second;

    for (int i = 2; i < n; ++i) {
        long long current = modPow(a[i], value);
        if ((current - previous + m) % m != diff) {
            stream.quitf(_wa, "K=%lld does not make the sequence arithmetic modulo M at index %d", value, i + 1);
        }
        previous = current;
    }

    return {false, value};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readLong();
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readLong();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim no valid K");
        }
        quitf(_fail, "participant found valid K=%lld while jury output is -1", participant.k);
    }

    if (participant.impossible) {
        quitf(_wa, "jury has valid K=%lld, but participant output is -1", jury.k);
    }

    quitf(_ok, "valid K=%lld", participant.k);
}
