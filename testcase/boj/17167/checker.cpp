#include "testlib.h"

#include <boost/multiprecision/cpp_int.hpp>
#include <string>

using namespace std;
using boost::multiprecision::cpp_int;

struct Claim {
    int steps;
};

Claim readClaim(InStream& stream, TResult verdict, const cpp_int& initialA, const cpp_int& initialB) {
    int n = stream.readInt(0, 5000, "n");

    cpp_int a = initialA;
    cpp_int b = initialB;
    for (int i = 0; i < n; ++i) {
        string op = stream.readToken("A\\+=A|A\\+=B|B\\+=A|B\\+=B", format("operation[%d]", i + 1));
        if (op == "A+=A") {
            a += a;
        } else if (op == "A+=B") {
            a += b;
        } else if (op == "B+=A") {
            b += a;
        } else if (op == "B+=B") {
            b += b;
        } else {
            stream.quitf(verdict, "operation[%d] has invalid value '%s'", i + 1, op.c_str());
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(verdict, "extra output after operation list");
    }

    if (a != b) {
        stream.quitf(verdict, "operations leave A and B unequal");
    }

    return {n};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    cpp_int initialA = inf.readLong(1LL, 1000000000000000000LL, "A");
    cpp_int initialB = inf.readLong(1LL, 1000000000000000000LL, "B");

    Claim jury = readClaim(ans, _fail, initialA, initialB);
    Claim participant = readClaim(ouf, _wa, initialA, initialB);

    quitf(_ok, "valid sequence with %d steps; jury used %d steps", participant.steps, jury.steps);
}
