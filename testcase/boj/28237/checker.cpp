#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

struct Output {
    bool impossible;
    long long a;
    long long b;
    long long c;
    long long d;
};

long long n;

static vector<string> readTokens(InStream& stream) {
    vector<string> tokens;
    while (!stream.seekEof()) {
        tokens.push_back(stream.readToken());
    }
    return tokens;
}

static bool matchesTarget(long long a, long long b, long long c, long long d) {
    __int128 xx = (__int128)a * c;
    __int128 x = (__int128)a * d + (__int128)b * c;
    __int128 constant = (__int128)b * d;
    return xx == n && x == n + 1 && constant == -(n + 2);
}

static Output readOutput(InStream& stream) {
    vector<string> tokens = readTokens(stream);

    if (tokens.size() == 1 && tokens[0] == "-1") {
        return {true, 0, 0, 0, 0};
    }

    if (tokens.size() != 4) {
        stream.quitf(_wa, "expected either -1 or four integers, found %d token(s)",
                     (int)tokens.size());
    }

    long long a = stringToLongLong(stream, tokens[0]);
    long long b = stringToLongLong(stream, tokens[1]);
    long long c = stringToLongLong(stream, tokens[2]);
    long long d = stringToLongLong(stream, tokens[3]);

    if (!matchesTarget(a, b, c, d)) {
        stream.quitf(_wa,
                     "invalid factorization: (%lldx%+lld)(%lldx%+lld) is not "
                     "%lldx^2%+lldx%+lld",
                     a, b, c, d, n, n + 1, -(n + 2));
    }

    return {false, a, b, c, d};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readLong();

    Output jury = readOutput(ans);
    Output participant = readOutput(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail,
              "participant found valid factorization while jury claims impossible: "
              "%lld %lld %lld %lld",
              participant.a, participant.b, participant.c, participant.d);
    }

    if (participant.impossible) {
        quitf(_wa, "jury has a valid factorization but participant claims impossible");
    }

    quitf(_ok, "valid factorization");
}
