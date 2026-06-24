#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int n, k;

struct Answer {
    bool impossible;
    int coprimeCount;
};

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, n, "first output token");

    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, 0};
    }
    if (first == 0) {
        stream.quitf(_wa, "permutation value 1 is 0");
    }

    vector<unsigned char> seen(n + 1, 0);
    seen[first] = 1;

    int coprimeCount = gcd(first, 1) == 1 ? 1 : 0;
    for (int i = 2; i <= n; ++i) {
        int value = stream.readInt(1, n, format("p[%d]", i).c_str());
        if (seen[value]) {
            stream.quitf(_wa, "value %d appears more than once", value);
        }
        seen[value] = 1;
        if (gcd(value, i) == 1) {
            ++coprimeCount;
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after permutation");
    }

    if (coprimeCount != k) {
        stream.quitf(_wa, "expected %d coprime positions, found %d", k, coprimeCount);
    }
    return {false, coprimeCount};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 1000000, "n");
    k = inf.readInt(0, n, "k");

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid permutation while jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible but jury provides a valid permutation");
    }

    quitf(_ok, "valid permutation with %d coprime positions", participant.coprimeCount);
}
