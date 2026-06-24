#include "testlib.h"

#include <boost/multiprecision/cpp_dec_float.hpp>

#include <algorithm>
#include <string>

using namespace std;
using Real = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<1200>>;

const Real EPS("1e-1000");

Real readAnswer(InStream& stream, const char* name) {
    string token = stream.readToken();
    if (token.size() > 5000) {
        stream.quitf(_wa, "%s answer is too long", name);
    }

    Real value;
    try {
        value = Real(token);
    } catch (...) {
        stream.quitf(_wa, "%s answer is not a valid real number", name);
    }

    if (!isfinite(value)) {
        stream.quitf(_wa, "%s answer is not finite", name);
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %s answer", name);
    }

    return value;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Real jury = readAnswer(ans, "jury");
    Real participant = readAnswer(ouf, "participant");

    Real delta = abs(participant - jury);
    Real scale = max(abs(jury), Real(1));
    if (delta <= EPS || delta <= EPS * scale) {
        quitf(_ok, "answer is within 1e-1000 absolute or relative error");
    }

    quitf(_wa, "answer differs from jury answer by more than 1e-1000");
}
