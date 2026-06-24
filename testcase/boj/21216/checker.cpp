#include "testlib.h"

#include <cstdlib>

using namespace std;

long long readClaim(InStream& stream, TResult verdict, const char* name) {
    long long value = stream.readLong(-1, 1000000000000000000LL, name);
    if (!stream.seekEof()) {
        stream.quitf(verdict, "extra output after %s", name);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    long long jury = readClaim(ans, _fail, "jury answer");
    long long participant = readClaim(ouf, _wa, "participant answer");

    if (jury == -1) {
        if (participant == -1) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_wa, "jury reports impossible, participant reported %lld", participant);
    }

    if (participant == -1) {
        quitf(_wa, "jury reports %lld days, participant reports impossible", jury);
    }

    if (participant == jury || llabs(participant - jury) == 1) {
        quitf(_ok, "accepted day count %lld with jury baseline %lld", participant, jury);
    }

    quitf(_wa, "expected %lld or adjacent accepted day count, found %lld", jury, participant);
}
