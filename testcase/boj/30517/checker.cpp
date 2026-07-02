#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> people;

struct Claim {
    bool impossible = false;
    int m = -1;
    int methodCount = 0;
    bool hasTerminator = false;
};

bool hasAdjacentCouple(const vector<int>& arranged) {
    for (int i = 1; i < int(arranged.size()); ++i) {
        if (arranged[i] != 0 && arranged[i] == arranged[i - 1]) {
            return true;
        }
    }
    return false;
}

Claim readClaim(InStream& stream) {
    int first = stream.readInt(-1, n, "minimum block count or -1");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after impossible sentinel");
        }
        return {.impossible = true};
    }

    Claim claim;
    claim.m = first;
    set<vector<int>> seen;
    while (!stream.seekEof()) {
        int next = stream.readInt(-1, n, format("method %d first block size or terminator", claim.methodCount + 1).c_str());
        if (next == -1) {
            claim.hasTerminator = true;
            if (!stream.seekEof()) {
                stream.quitf(_wa, "extra output after -1 terminator");
            }
            break;
        }

        vector<int> sizes(claim.m);
        sizes[0] = next;
        int total = sizes[0];
        for (int i = 1; i < claim.m; ++i) {
            sizes[i] = stream.readInt(1, n, format("method %d block size %d", claim.methodCount + 1, i + 1).c_str());
            total += sizes[i];
            if (total > n) {
                stream.quitf(_wa, "method %d block sizes exceed N", claim.methodCount + 1);
            }
        }
        if (total != n) {
            stream.quitf(_wa, "method %d block sizes sum to %d instead of %d", claim.methodCount + 1, total, n);
        }

        vector<int> perm(claim.m);
        vector<int> used(claim.m + 1, 0);
        for (int i = 0; i < claim.m; ++i) {
            perm[i] = stream.readInt(1, claim.m, format("method %d permutation %d", claim.methodCount + 1, i + 1).c_str());
            if (used[perm[i]]) {
                stream.quitf(_wa, "method %d repeats block %d in permutation", claim.methodCount + 1, perm[i]);
            }
            used[perm[i]] = 1;
        }

        vector<int> starts(claim.m), ends(claim.m);
        int pos = 0;
        for (int i = 0; i < claim.m; ++i) {
            starts[i] = pos;
            pos += sizes[i];
            ends[i] = pos;
        }

        vector<int> arranged;
        arranged.reserve(n);
        for (int blockNumber : perm) {
            int block = blockNumber - 1;
            for (int i = starts[block]; i < ends[block]; ++i) {
                arranged.push_back(people[i]);
            }
        }
        if (hasAdjacentCouple(arranged)) {
            stream.quitf(_wa, "method %d leaves a couple adjacent after rearranging blocks", claim.methodCount + 1);
        }

        vector<int> key;
        key.reserve(2 * claim.m);
        key.insert(key.end(), sizes.begin(), sizes.end());
        key.insert(key.end(), perm.begin(), perm.end());
        if (!seen.insert(key).second) {
            stream.quitf(_wa, "method %d duplicates an earlier method", claim.methodCount + 1);
        }

        ++claim.methodCount;
        if (claim.methodCount > 100) {
            stream.quitf(_wa, "more than 100 methods are listed");
        }
    }

    if (claim.methodCount == 0) {
        stream.quitf(_wa, "no method is listed for possible answer");
    }
    if (claim.methodCount < 100 && !claim.hasTerminator) {
        stream.quitf(_wa, "missing -1 terminator after fewer than 100 methods");
    }
    if (claim.methodCount == 100 && claim.hasTerminator) {
        stream.quitf(_wa, "unexpected -1 terminator after 100 methods");
    }
    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 1000, "N");
    people.resize(n);
    for (int i = 0; i < n; ++i) {
        people[i] = inf.readInt(0, 1000, format("a[%d]", i + 1).c_str());
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant provided %d valid method(s) with M=%d while jury claims impossible",
              participant.methodCount, participant.m);
    }
    if (participant.impossible) {
        quitf(_wa, "participant claims impossible while jury has M=%d", jury.m);
    }

    if (participant.m < jury.m) {
        quitf(_fail, "participant found valid methods with fewer blocks: jury=%d participant=%d",
              jury.m, participant.m);
    }
    if (participant.m > jury.m) {
        quitf(_wa, "participant uses more blocks than jury: jury=%d participant=%d", jury.m, participant.m);
    }
    if (participant.methodCount < jury.methodCount) {
        quitf(_wa, "participant lists fewer methods than jury: jury=%d participant=%d",
              jury.methodCount, participant.methodCount);
    }
    if (participant.methodCount > jury.methodCount) {
        quitf(_fail, "participant lists more valid methods than jury: jury=%d participant=%d",
              jury.methodCount, participant.methodCount);
    }
    if (participant.hasTerminator != jury.hasTerminator) {
        quitf(_wa, "participant terminator does not match jury terminator");
    }

    quitf(_ok, "M=%d, methods=%d", participant.m, participant.methodCount);
}
