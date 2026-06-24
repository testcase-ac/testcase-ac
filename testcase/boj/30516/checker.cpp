#include "testlib.h"

#include <vector>

using namespace std;

struct Claim {
    bool impossible;
    int m;
};

int n;
vector<int> a;

Claim readClaim(InStream& stream) {
    int m = stream.readInt(-1, n, "M");
    if (m == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, -1};
    }
    if (m == 0) {
        stream.quitf(_wa, "M must be positive or -1");
    }

    vector<int> sizes(m);
    int total = 0;
    for (int i = 0; i < m; ++i) {
        sizes[i] = stream.readInt(1, n, format("size[%d]", i + 1).c_str());
        total += sizes[i];
        if (total > n) {
            stream.quitf(_wa, "sum of sizes exceeds N at size[%d]", i + 1);
        }
    }
    if (total != n) {
        stream.quitf(_wa, "sum of sizes is %d, expected %d", total, n);
    }

    vector<int> order(m);
    vector<int> used(m, 0);
    for (int i = 0; i < m; ++i) {
        order[i] = stream.readInt(1, m, format("order[%d]", i + 1).c_str()) - 1;
        if (used[order[i]]) {
            stream.quitf(_wa, "chunk %d appears more than once in order", order[i] + 1);
        }
        used[order[i]] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after chunk order");
    }

    vector<int> start(m);
    for (int i = 1; i < m; ++i) {
        start[i] = start[i - 1] + sizes[i - 1];
    }

    vector<int> arranged;
    arranged.reserve(n);
    for (int chunk : order) {
        for (int i = start[chunk]; i < start[chunk] + sizes[chunk]; ++i) {
            arranged.push_back(a[i]);
        }
    }

    for (int i = 1; i < n; ++i) {
        if (arranged[i] != 0 && arranged[i] == arranged[i - 1]) {
            stream.quitf(_wa,
                         "couple value %d is adjacent after reordering at positions %d and %d",
                         arranged[i], i, i + 1);
        }
    }

    return {false, m};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 1000, "N");
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readInt(0, 1000, format("a[%d]", i + 1).c_str());
    }

    Claim jury = readClaim(ans);
    Claim part = readClaim(ouf);

    if (jury.impossible) {
        if (part.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant found a valid arrangement with M=%d while jury says impossible", part.m);
    }

    if (part.impossible) {
        quitf(_wa, "participant says impossible, but jury has M=%d", jury.m);
    }
    if (part.m > jury.m) {
        quitf(_wa, "participant uses M=%d chunks, but jury uses M=%d", part.m, jury.m);
    }
    if (part.m < jury.m) {
        quitf(_fail, "participant found a valid arrangement with fewer chunks: participant=%d jury=%d",
              part.m, jury.m);
    }

    quitf(_ok, "valid arrangement with M=%d", part.m);
}
