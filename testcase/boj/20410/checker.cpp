#include "testlib.h"

using namespace std;

struct Claim {
    int a;
    int c;
};

enum class StreamRole {
    Jury,
    Participant,
};

int m;
int seedValue;
int x1;
int x2;

long long nextValue(const Claim& claim, int value) {
    return (1LL * claim.a * value + claim.c) % m;
}

void quitInvalid(InStream& stream, StreamRole role, const char* message) {
    if (role == StreamRole::Jury) {
        stream.quitf(_fail, "%s", message);
    }
    stream.quitf(_wa, "%s", message);
}

Claim readClaim(InStream& stream, StreamRole role) {
    Claim claim;
    claim.a = stream.readInt(0, m - 1, "a");
    claim.c = stream.readInt(0, m - 1, "c");
    if (!stream.seekEof()) {
        quitInvalid(stream, role, "extra output after a and c");
    }

    long long generatedX1 = nextValue(claim, seedValue);
    if (generatedX1 != x1) {
        if (role == StreamRole::Jury) {
            stream.quitf(_fail, "jury a=%d c=%d generates X_1=%lld instead of %d",
                         claim.a, claim.c, generatedX1, x1);
        }
        stream.quitf(_wa, "a=%d c=%d generates X_1=%lld instead of %d",
                     claim.a, claim.c, generatedX1, x1);
    }

    long long generatedX2 = nextValue(claim, x1);
    if (generatedX2 != x2) {
        if (role == StreamRole::Jury) {
            stream.quitf(_fail, "jury a=%d c=%d generates X_2=%lld instead of %d",
                         claim.a, claim.c, generatedX2, x2);
        }
        stream.quitf(_wa, "a=%d c=%d generates X_2=%lld instead of %d",
                     claim.a, claim.c, generatedX2, x2);
    }

    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    m = inf.readInt();
    seedValue = inf.readInt();
    x1 = inf.readInt();
    x2 = inf.readInt();

    readClaim(ans, StreamRole::Jury);
    Claim participant = readClaim(ouf, StreamRole::Participant);

    quitf(_ok, "valid a=%d c=%d", participant.a, participant.c);
}
