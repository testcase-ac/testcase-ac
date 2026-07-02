#include "testlib.h"

#include <string>

using namespace std;

long long target;

struct Claim {
    bool impossible;
    string witness;
};

long long encryptedValue(const string& digits) {
    __int128 total = 0;
    __int128 count = 0;

    for (char ch : digits) {
        int digit = ch - '0';
        total = 11 * total + digit * (count + 1);
        count = 2 * count + 1;
        if (total > target) {
            return target + 1;
        }
    }

    return (long long)total;
}

Claim readClaim(InStream& stream) {
    string token = stream.readToken("NIE|[1-9][0-9]{0,18}", "answer");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }

    if (token == "NIE") {
        return {true, ""};
    }

    if (encryptedValue(token) != target) {
        stream.quitf(_wa, "witness %s encrypts to a value different from %lld",
                     token.c_str(), target);
    }

    return {false, token};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    target = inf.readLong(1LL, 1000000000000000000LL, "n");

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim NIE");
        }
        quitf(_fail, "participant found valid witness %s while jury says NIE",
              participant.witness.c_str());
    }

    if (participant.impossible) {
        quitf(_wa, "participant says NIE, but jury has witness %s", jury.witness.c_str());
    }

    quitf(_ok, "valid witness %s", participant.witness.c_str());
}
