#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

long long N;

struct Answer {
    bool impossible;
};

Answer readAns(InStream& stream) {
    long long first = stream.readLong(-1, N, "first output token");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }
    long long second = stream.readLong(0, N, "second square root");
    long long third = stream.readLong(0, N, "third square root");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after representation");
    }

    __int128 sum = (__int128)first * first + (__int128)second * second + (__int128)third * third;
    if (sum != N) {
        stream.quitf(_wa, "%lld^2 + %lld^2 + %lld^2 does not equal %lld",
                     first, second, third, N);
    }
    return {false};
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    N = inf.readLong();

    Answer jury = readAns(ans);
    Answer participant = readAns(ouf);

    if (jury.impossible && participant.impossible) {
        quitf(_ok, "both outputs report impossible");
    }
    if (jury.impossible && !participant.impossible) {
        quitf(_fail, "participant supplied a valid representation while jury reports impossible");
    }
    if (!jury.impossible && participant.impossible) {
        quitf(_wa, "participant reports impossible while jury has a representation");
    }

    quitf(_ok, "valid representation");
}
