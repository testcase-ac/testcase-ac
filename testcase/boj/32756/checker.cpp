#include "testlib.h"

#include <boost/multiprecision/cpp_int.hpp>
#include <string>

using boost::multiprecision::cpp_int;
using namespace std;

const int MAX_L = 1000;

long long targetN, targetD;

struct Claim {
    bool impossible;
};

Claim readClaim(InStream& stream) {
    long long first = stream.readLong(-1LL, (long long)MAX_L, "path length or -1");

    if (first == -1) {
        stream.readEoln();
        stream.readEof();
        return {true};
    }

    int length = int(first);
    stream.readEoln();
    string path = stream.readLine();
    if ((int)path.size() != length) {
        stream.quitf(_wa, "path length is %d but declared length is %d",
                     (int)path.size(), length);
    }
    stream.readEof();

    cpp_int scale = cpp_int(1) << MAX_L;
    cpp_int a = 0;
    cpp_int b = scale;

    for (int i = 0; i < length; ++i) {
        char c = path[i];
        if (c == 'R') {
            a += b;
        } else if (c == 'L') {
            a -= b;
        } else if (c == 'U') {
            b <<= 1;
        } else if (c == 'D') {
            b >>= 1;
        } else {
            stream.quitf(_wa, "path[%d] is '%c', expected one of R, L, U, D",
                         i + 1, c);
        }
    }

    if (a * targetD != cpp_int(targetN) * scale) {
        stream.quitf(_wa, "path does not produce the target fraction");
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    targetN = inf.readLong();
    targetD = inf.readLong();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant found a valid path while jury claims impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "jury provides a valid path but participant claims impossible");
    }

    quitf(_ok, "valid path");
}
