#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Claim {
    long long a;
    long long b;
    long long c;
    char op1;
    char op2;
};

long long signedSquare(long long x, char op) {
    long long value = x * x;
    return op == '+' ? value : -value;
}

Claim readClaim(InStream& stream, int tc, long long k, TResult verdict) {
    Claim claim;
    claim.a = stream.readLong(1, 1000000000LL, format("a[%d]", tc).c_str());

    string first = stream.readToken("[+-]", format("op1[%d]", tc).c_str());
    claim.op1 = first[0];

    claim.b = stream.readLong(1, 1000000000LL, format("b[%d]", tc).c_str());

    string second = stream.readToken("[+-]", format("op2[%d]", tc).c_str());
    claim.op2 = second[0];

    claim.c = stream.readLong(1, 1000000000LL, format("c[%d]", tc).c_str());
    stream.readEoln();

    long long value = claim.a * claim.a + signedSquare(claim.b, claim.op1) + signedSquare(claim.c, claim.op2);
    if (value != k) {
        stream.quitf(verdict,
                     "case %d: %lld %c %lld %c %lld gives %lld, expected %lld",
                     tc,
                     claim.a,
                     claim.op1,
                     claim.b,
                     claim.op2,
                     claim.c,
                     value,
                     k);
    }

    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    vector<long long> k(t + 1);
    for (int tc = 1; tc <= t; ++tc) {
        k[tc] = inf.readLong();
    }

    for (int tc = 1; tc <= t; ++tc) {
        readClaim(ans, tc, k[tc], _fail);
        readClaim(ouf, tc, k[tc], _wa);
    }

    ans.readEof();
    ouf.readEof();

    quitf(_ok, "all %d certificates are valid", t);
}
