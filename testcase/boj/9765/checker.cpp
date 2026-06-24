#include "testlib.h"

using namespace std;

namespace {

constexpr long long MIN_PRIME = 2;
constexpr long long MAX_PRIME = 20000000LL;

struct Input {
    long long c1;
    long long c3;
    long long c5;
    long long c6;
};

struct Answer {
    long long x1;
    long long x2;
    long long x3;
    long long x5;
    long long x6;
    long long x7;
};

bool isPrime(long long value) {
    if (value < 2) {
        return false;
    }
    if (value % 2 == 0) {
        return value == 2;
    }
    for (long long divisor = 3; divisor * divisor <= value; divisor += 2) {
        if (value % divisor == 0) {
            return false;
        }
    }
    return true;
}

long long readPrime(InStream& stream, const char* name) {
    long long value = stream.readLong(MIN_PRIME, MAX_PRIME, name);
    if (!isPrime(value)) {
        stream.quitf(_wa, "%s must be prime, got %lld", name, value);
    }
    return value;
}

Answer readAnswer(InStream& stream, const Input& input) {
    Answer answer;
    answer.x1 = readPrime(stream, "x_1");
    answer.x2 = readPrime(stream, "x_2");
    answer.x3 = readPrime(stream, "x_3");
    answer.x5 = readPrime(stream, "x_5");
    answer.x6 = readPrime(stream, "x_6");
    answer.x7 = readPrime(stream, "x_7");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after x_7");
    }

    if (answer.x1 * answer.x2 != input.c1) {
        stream.quitf(_wa, "x_1 * x_2 must be %lld, got %lld",
                     input.c1, answer.x1 * answer.x2);
    }
    if (answer.x6 * answer.x7 != input.c3) {
        stream.quitf(_wa, "x_6 * x_7 must be %lld, got %lld",
                     input.c3, answer.x6 * answer.x7);
    }
    if (answer.x2 * answer.x3 != input.c5) {
        stream.quitf(_wa, "x_2 * x_3 must be %lld, got %lld",
                     input.c5, answer.x2 * answer.x3);
    }
    if (answer.x6 * answer.x5 != input.c6) {
        stream.quitf(_wa, "x_6 * x_5 must be %lld, got %lld",
                     input.c6, answer.x6 * answer.x5);
    }

    return answer;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Input input;
    input.c1 = inf.readLong();
    inf.readLong();
    input.c3 = inf.readLong();
    inf.readLong();
    input.c5 = inf.readLong();
    input.c6 = inf.readLong();

    readAnswer(ans, input);
    readAnswer(ouf, input);

    quitf(_ok, "valid solution");
}
