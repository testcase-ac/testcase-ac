#include "testlib.h"

#include <string>

using namespace std;

int n, l;

int bottomNumber(string value) {
    while (value.size() > 1) {
        long long product = 1;
        for (char c : value) {
            product *= c - '0';
        }
        value = to_string(product);
    }
    return value[0] - '0';
}

struct Claim {
    string value;
    int bottom;
};

Claim readClaim(InStream& stream) {
    string value = stream.readToken("[0-9]+", "P");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after P");
    }

    if ((int)value.size() != l) {
        stream.quitf(_wa, "P has %d digits instead of %d", (int)value.size(), l);
    }
    if (value[0] == '0') {
        stream.quitf(_wa, "P must not start with zero");
    }

    int bottom = bottomNumber(value);
    if (bottom != n) {
        stream.quitf(_wa, "P has bottom number %d instead of %d", bottom, n);
    }

    return {value, bottom};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    l = inf.readInt();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.bottom != jury.bottom) {
        quitf(_wa, "participant bottom number %d differs from jury bottom number %d",
              participant.bottom, jury.bottom);
    }

    quitf(_ok, "P=%s has bottom number %d", participant.value.c_str(), participant.bottom);
}
