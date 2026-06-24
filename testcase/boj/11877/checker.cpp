#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int n;
long long x;

struct Claim {
    bool impossible;
};

long long capacityOf(const vector<int>& h) {
    vector<int> rightMax(n);
    int best = 0;
    for (int i = n - 1; i >= 0; --i) {
        best = max(best, h[i]);
        rightMax[i] = best;
    }

    long long capacity = 0;
    int leftMax = 0;
    for (int i = 0; i < n; ++i) {
        leftMax = max(leftMax, h[i]);
        int waterLevel = min(leftMax, rightMax[i]);
        if (waterLevel > h[i]) {
            capacity += waterLevel - h[i];
        }
    }
    return capacity;
}

Claim readClaim(InStream& stream) {
    int first = stream.readInt(-1, n, "first output token");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }
    if (first < 1) {
        stream.quitf(_wa, "first height must be -1 or in [1, %d], found %d", n, first);
    }

    vector<int> h(n);
    vector<char> seen(n + 1, 0);
    h[0] = first;
    seen[first] = 1;

    for (int i = 1; i < n; ++i) {
        h[i] = stream.readInt(1, n, format("h[%d]", i + 1).c_str());
        if (seen[h[i]]) {
            stream.quitf(_wa, "height %d appears more than once", h[i]);
        }
        seen[h[i]] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after histogram");
    }

    long long capacity = capacityOf(h);
    if (capacity != x) {
        stream.quitf(_wa, "histogram capacity is %lld, expected %lld", capacity, x);
    }
    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    x = inf.readLong();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible && !participant.impossible) {
        quitf(_fail, "participant found a valid histogram while jury says impossible");
    }
    if (!jury.impossible && participant.impossible) {
        quitf(_wa, "participant says impossible but jury provides a valid histogram");
    }

    quitf(_ok, jury.impossible ? "both outputs say impossible" : "valid histogram");
}
