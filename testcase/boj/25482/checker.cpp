#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

int n;
vector<long long> initialValues;

struct Claim {
    long long value;
};

Claim readClaim(InStream& stream) {
    long long claimed = stream.readLong((long long)-4e18, (long long)4e18, "final value");

    set<int> alive;
    vector<long long> value(n + 1);
    for (int i = 1; i <= n; ++i) {
        alive.insert(i);
        value[i] = initialValues[i];
    }

    for (int step = 1; step <= n - 1; ++step) {
        int position = stream.readInt(2, n, format("move[%d]", step).c_str());
        auto it = alive.find(position);
        if (it == alive.end()) {
            stream.quitf(_wa, "move %d pushes position %d, but no marble is there", step, position);
        }
        if (it == alive.begin()) {
            stream.quitf(_wa, "move %d pushes position %d with no marble to its left", step, position);
        }

        auto left = prev(it);
        value[*left] -= value[position];
        alive.erase(it);
    }

    if (alive.size() != 1 || *alive.begin() != 1) {
        stream.quitf(_wa, "sequence does not leave exactly the marble at position 1");
    }

    long long actual = value[1];
    if (claimed != actual) {
        stream.quitf(_wa, "claimed final value %lld does not match sequence value %lld", claimed, actual);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after move sequence");
    }
    return {actual};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 100000, "N");
    initialValues.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        initialValues[i] = inf.readLong((long long)-1000000000, (long long)1000000000,
                                        format("A[%d]", i).c_str());
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.value < jury.value) {
        quitf(_wa, "jury has better final value: jury=%lld participant=%lld", jury.value,
              participant.value);
    }
    if (participant.value > jury.value) {
        quitf(_fail, "participant found better final value: jury=%lld participant=%lld", jury.value,
              participant.value);
    }
    quitf(_ok, "final value %lld", participant.value);
}
