#include "testlib.h"

#include <vector>

using namespace std;

int n;
long long k;

struct Answer {
    bool impossible;
};

long long inversionCount(const vector<int>& p) {
    vector<int> bit(n + 1, 0);

    auto add = [&](int index) {
        for (; index <= n; index += index & -index) {
            ++bit[index];
        }
    };

    auto sum = [&](int index) {
        int result = 0;
        for (; index > 0; index -= index & -index) {
            result += bit[index];
        }
        return result;
    };

    long long inversions = 0;
    for (int i = 0; i < n; ++i) {
        inversions += i - sum(p[i]);
        add(p[i]);
    }
    return inversions;
}

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, n, "p[1] or -1");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }
    if (first == 0) {
        stream.quitf(_wa, "p[1] must be in [1, %d] or -1", n);
    }

    vector<int> p(n);
    vector<int> used(n + 1, 0);
    p[0] = first;
    used[first] = 1;

    for (int i = 1; i < n; ++i) {
        p[i] = stream.readInt(1, n, format("p[%d]", i + 1).c_str());
        if (used[p[i]]) {
            stream.quitf(_wa, "value %d appears more than once", p[i]);
        }
        used[p[i]] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after permutation");
    }

    long long actual = inversionCount(p);
    if (actual != k) {
        stream.quitf(_wa, "permutation has %lld inversions, expected %lld", actual, k);
    }
    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readLong();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant found a valid permutation while jury says impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant says impossible, but jury provides a valid permutation");
    }

    quitf(_ok, "valid permutation with %lld inversions", k);
}
