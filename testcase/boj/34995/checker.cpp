#include "testlib.h"

#include <string>

using namespace std;

int n;
string pattern;
string price;

struct Claim {
    bool impossible;
    string coupon;
};

bool atLeastPrice(const string& coupon) {
    if (coupon.size() != price.size()) {
        return coupon.size() > price.size();
    }
    return coupon >= price;
}

Claim readClaim(InStream& stream) {
    string token = stream.readToken("[^\\s]+", "answer");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }

    if (token == "-1") {
        return {true, ""};
    }

    if ((int)token.size() != n) {
        stream.quitf(_wa, "coupon length is %d, expected %d", (int)token.size(), n);
    }

    for (int i = 0; i < n; ++i) {
        if (token[i] < '1' || token[i] > '9') {
            stream.quitf(_wa, "coupon[%d] is '%c', expected a digit from 1 to 9", i + 1, token[i]);
        }
        if (pattern[i] != '?' && token[i] != pattern[i]) {
            stream.quitf(_wa, "coupon[%d] is '%c', expected fixed digit '%c'",
                         i + 1, token[i], pattern[i]);
        }
    }

    if (!atLeastPrice(token)) {
        stream.quitf(_wa, "coupon value is smaller than the food price");
    }

    return {false, token};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    pattern = inf.readToken();
    price = inf.readToken();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid coupon while jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible, but jury provides a valid coupon");
    }

    quitf(_ok, "valid coupon");
}
