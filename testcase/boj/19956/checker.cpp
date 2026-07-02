#include "testlib.h"

#include <boost/multiprecision/cpp_int.hpp>

#include <cctype>
#include <string>

using namespace std;
using boost::multiprecision::cpp_int;

const int MAX_PRIME_CODE = 1000000000;
const int MAX_OPERATIONS_WITHOUT_BASELINE = 100000;

long long initialN;
long long targetM;

struct Answer {
    bool impossible;
    bool tooLong;
    int operations;
};

bool parseNonNegativeInt(const string& token, int& value) {
    if (token.empty()) {
        return false;
    }
    long long parsed = 0;
    for (char ch : token) {
        if (!isdigit((unsigned char)ch)) {
            return false;
        }
        parsed = parsed * 10 + (ch - '0');
        if (parsed > MAX_PRIME_CODE) {
            return false;
        }
    }
    value = (int)parsed;
    return true;
}

bool isPrime(int x) {
    if (x < 2) {
        return false;
    }
    for (long long d = 2; d * d <= x; ++d) {
        if (x % d == 0) {
            return false;
        }
    }
    return true;
}

Answer readAnswer(InStream& stream, int maxOperations) {
    if (stream.seekEof()) {
        if (initialN != targetM) {
            stream.quitf(_wa, "empty sequence does not reach m");
        }
        return {false, false, 0};
    }

    string token = stream.readToken("Impossible|[0-9]+", "first output token");

    if (token == "Impossible") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after Impossible");
        }
        return {true, false, 0};
    }

    cpp_int current = initialN;
    int operations = 0;

    while (true) {
        ++operations;
        if (operations > maxOperations) {
            return {false, true, operations};
        }

        int op = 0;
        if (!parseNonNegativeInt(token, op)) {
            stream.quitf(_wa, "operation %d is not an integer between 0 and %d",
                         operations, MAX_PRIME_CODE);
        }

        if (op == 0) {
            current *= current;
        } else {
            if (!isPrime(op)) {
                stream.quitf(_wa, "operation %d uses non-prime divisor %d", operations, op);
            }
            if (current % op != 0) {
                stream.quitf(_wa, "operation %d divides by %d, but current value is not divisible by it",
                             operations, op);
            }
            current /= op;
        }

        if (stream.seekEof()) {
            break;
        }
        token = stream.readToken("[0-9]+", format("operation %d", operations + 1).c_str());
    }

    if (current != targetM) {
        stream.quitf(_wa, "sequence ends at a value different from m");
    }
    return {false, false, operations};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    initialN = inf.readLong(1LL, 1000000000LL, "n");
    targetM = inf.readLong(1LL, 1000000000LL, "m");

    Answer jury = readAnswer(ans, MAX_OPERATIONS_WITHOUT_BASELINE);
    if (jury.tooLong) {
        quitf(_fail, "jury sequence exceeds %d operations", MAX_OPERATIONS_WITHOUT_BASELINE);
    }

    int participantLimit = jury.impossible ? MAX_OPERATIONS_WITHOUT_BASELINE : jury.operations + 1;
    Answer participant = readAnswer(ouf, participantLimit);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report Impossible");
        }
        if (participant.tooLong) {
            quitf(_wa, "participant sequence exceeds %d operations", participantLimit);
        }
        quitf(_fail, "participant provides a valid sequence while jury reports Impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "jury provides a valid sequence, but participant reports Impossible");
    }
    if (participant.tooLong || participant.operations > jury.operations) {
        quitf(_wa, "participant sequence is longer than jury sequence: participant>%d jury=%d",
              jury.operations, jury.operations);
    }
    if (participant.operations < jury.operations) {
        quitf(_fail, "participant found a shorter valid sequence: participant=%d jury=%d",
              participant.operations, jury.operations);
    }

    quitf(_ok, "valid shortest sequence with %d operations", participant.operations);
}
