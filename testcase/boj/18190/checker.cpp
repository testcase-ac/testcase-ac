#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

struct Claim {
    enum Kind {
        Out,
        In,
        Area,
    } kind;
    double area;
};

Claim readClaim(InStream& stream, int index) {
    string token = stream.readToken();
    if (token == "OUT") {
        return {Claim::Out, 0.0};
    }
    if (token == "IN") {
        return {Claim::In, 0.0};
    }

    char* end = nullptr;
    errno = 0;
    double value = strtod(token.c_str(), &end);
    if (end == token.c_str() || *end != '\0' || errno == ERANGE || !isfinite(value)) {
        stream.quitf(_wa, "answer[%d] is neither OUT, IN, nor a finite real number: %s",
                     index + 1, token.c_str());
    }
    return {Claim::Area, value};
}

const char* kindName(Claim::Kind kind) {
    if (kind == Claim::Out) return "OUT";
    if (kind == Claim::In) return "IN";
    return "area";
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    int q = inf.readInt();

    for (int i = 0; i < n + m; ++i) {
        inf.readLong();
        inf.readLong();
    }
    for (int i = 0; i < q; ++i) {
        inf.readLong();
        inf.readLong();
    }

    for (int i = 0; i < q; ++i) {
        Claim jury = readClaim(ans, i);
        Claim participant = readClaim(ouf, i);

        if (jury.kind != participant.kind) {
            quitf(_wa, "answer[%d] has kind %s, expected %s",
                  i + 1, kindName(participant.kind), kindName(jury.kind));
        }
        if (jury.kind == Claim::Area &&
            !doubleCompare(jury.area, participant.area, EPS)) {
            quitf(_wa,
                  "answer[%d] expected %.12f, found %.12f, error %.12f",
                  i + 1, jury.area, participant.area,
                  doubleDelta(jury.area, participant.area));
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answers");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answers");
    }

    quitf(_ok, "all %d answers match the jury output", q);
}
