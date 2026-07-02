#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Fighter {
    long long minOpponents;
    long long maxOpponents;
};

int n;
long long k;
vector<Fighter> fighters;

struct Claim {
    bool success;
};

Claim readClaim(InStream& stream) {
    string verdict = stream.readToken("[A-Z]+", "verdict");
    if (verdict == "FAIL") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after FAIL");
        }
        return {false};
    }
    if (verdict != "SUCCESS") {
        stream.quitf(_wa, "expected FAIL or SUCCESS, found %s", verdict.c_str());
    }

    long long expectedLeft = 1;
    for (int i = 0; i < n; ++i) {
        long long left = stream.readLong(1, k, format("l[%d]", i + 1).c_str());
        long long right = stream.readLong(1, k, format("r[%d]", i + 1).c_str());

        if (left != expectedLeft) {
            stream.quitf(_wa,
                         "fighter %d interval starts at %lld, expected %lld",
                         i + 1,
                         left,
                         expectedLeft);
        }
        if (right < left) {
            stream.quitf(_wa, "fighter %d has empty or reversed interval", i + 1);
        }

        long long length = right - left + 1;
        if (length < fighters[i].minOpponents || length > fighters[i].maxOpponents) {
            stream.quitf(_wa,
                         "fighter %d covers %lld opponents, expected between %lld and %lld",
                         i + 1,
                         length,
                         fighters[i].minOpponents,
                         fighters[i].maxOpponents);
        }

        expectedLeft = right + 1;
    }

    if (expectedLeft != k + 1) {
        stream.quitf(_wa,
                     "intervals cover opponents 1..%lld, expected 1..%lld",
                     expectedLeft - 1,
                     k);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after SUCCESS assignment");
    }
    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readLong();
    fighters.resize(n);
    for (int i = 0; i < n; ++i) {
        long long a = inf.readLong();
        long long b = inf.readLong();
        fighters[i] = {max(1LL, a), b};
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.success == participant.success) {
        quitf(_ok, "%s", participant.success ? "valid SUCCESS assignment" : "matched FAIL");
    }
    if (!jury.success && participant.success) {
        quitf(_fail, "participant found a valid SUCCESS assignment while jury says FAIL");
    }
    quitf(_wa, "jury has a valid SUCCESS assignment, participant says FAIL");
}
