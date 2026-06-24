#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int n;

struct Answer {
    long long sum;
    int divisorCount;
};

Answer readAnswer(InStream& stream) {
    vector<int> a(n);
    set<int> seen;
    long long sum = 0;

    for (int i = 0; i < n; ++i) {
        a[i] = stream.readInt(2, 1000000, format("A[%d]", i + 1).c_str());
        if (!seen.insert(a[i]).second) {
            stream.quitf(_wa, "A[%d]=%d is repeated", i + 1, a[i]);
        }
        sum += a[i];
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after sequence");
    }

    int divisorCount = 0;
    for (int value : a) {
        if (sum % value == 0) {
            ++divisorCount;
        }
    }
    if (divisorCount != 1) {
        stream.quitf(_wa, "exactly one element must divide sum=%lld, found %d", sum, divisorCount);
    }

    return {sum, divisorCount};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 100000, "N");

    readAnswer(ans);
    Answer participant = readAnswer(ouf);

    quitf(_ok, "valid sequence with sum=%lld", participant.sum);
}
