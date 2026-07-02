#include "testlib.h"

#include <boost/multiprecision/cpp_int.hpp>
#include <string>

using boost::multiprecision::cpp_int;
using namespace std;

const cpp_int LIMIT = cpp_int("1000000000000000000");

cpp_int absInt(cpp_int x) {
    return x < 0 ? -x : x;
}

cpp_int readInteger(InStream& stream, const char* name) {
    string token = stream.readToken("-?[0-9]+", name);
    bool negative = false;
    size_t pos = 0;
    if (!token.empty() && token[0] == '-') {
        negative = true;
        pos = 1;
    }

    cpp_int value = 0;
    for (; pos < token.size(); ++pos) {
        value *= 10;
        value += token[pos] - '0';
    }
    return negative ? -value : value;
}

struct Answer {
    int steps;
};

Answer readAnswer(InStream& stream, cpp_int initialA, cpp_int initialB) {
    int n = stream.readInt(0, 50, "number of actions");
    stream.readEoln();

    cpp_int a = initialA;
    cpp_int b = initialB;

    for (int i = 0; i < n; ++i) {
        int t = stream.readInt(1, 2, format("t[%d]", i + 1).c_str());
        stream.readSpace();
        cpp_int k = readInteger(stream, format("k[%d]", i + 1).c_str());
        stream.readEoln();

        if (t == 1) {
            a += k * b;
            if (absInt(a) > LIMIT) {
                stream.quitf(_wa, "after action %d, first card exceeds 1e18", i + 1);
            }
        } else {
            b += k * a;
            if (absInt(b) > LIMIT) {
                stream.quitf(_wa, "after action %d, second card exceeds 1e18", i + 1);
            }
        }
    }

    stream.readEof();

    if (a != 0 && b != 0) {
        stream.quitf(_wa, "neither card is zero after %d actions", n);
    }

    return {n};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    long long inputA = inf.readLong(-1000000000000000000LL, 1000000000000000000LL, "a0");
    long long inputB = inf.readLong(-1000000000000000000LL, 1000000000000000000LL, "b0");
    cpp_int initialA = inputA;
    cpp_int initialB = inputB;

    Answer jury = readAnswer(ans, initialA, initialB);
    Answer participant = readAnswer(ouf, initialA, initialB);

    quitf(_ok, "valid sequence with %d actions; jury used %d actions", participant.steps, jury.steps);
}
