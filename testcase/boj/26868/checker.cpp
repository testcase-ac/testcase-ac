#include "testlib.h"

#include <cmath>
#include <string>

using namespace std;

const int MAX_OPERATIONS = 1000;
const double EPS = 1e-9;

int a, b;

struct Claim {
    int operations;
    double value;
};

bool isFinite(double value) {
    return isfinite(value);
}

double applyOperation(double value, const string& op, InStream& stream, int index) {
    double next;
    if (op == "sin") {
        next = sin(value);
    } else if (op == "cos") {
        next = cos(value);
    } else if (op == "tan") {
        next = tan(value);
    } else if (op == "asin") {
        if (value < -1.0 || value > 1.0) {
            stream.quitf(_wa, "operation %d: asin is inapplicable to %.17g", index, value);
        }
        next = asin(value);
    } else if (op == "acos") {
        if (value < -1.0 || value > 1.0) {
            stream.quitf(_wa, "operation %d: acos is inapplicable to %.17g", index, value);
        }
        next = acos(value);
    } else if (op == "atan") {
        next = atan(value);
    } else {
        stream.quitf(_wa, "operation %d: unknown operation '%s'", index, op.c_str());
    }

    if (!isFinite(next)) {
        stream.quitf(_wa, "operation %d: %s produced a non-finite value", index, op.c_str());
    }
    return next;
}

Claim readClaim(InStream& stream) {
    int k = stream.readInt(1, MAX_OPERATIONS, "k");
    double value = 0.0;

    for (int i = 0; i < k; ++i) {
        string operation = stream.readToken("[a-z]+", format("operation[%d]", i + 1).c_str());
        value = applyOperation(value, operation, stream, i + 1);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after operation sequence");
    }

    double target = static_cast<double>(a) / static_cast<double>(b);
    double error = fabs(value - target);
    if (error > EPS) {
        stream.quitf(_wa,
                     "final value %.17g differs from target %.17g by %.17g",
                     value,
                     target,
                     error);
    }

    return {k, value};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    a = inf.readInt();
    b = inf.readInt();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    quitf(_ok,
          "valid sequence with %d operations, final value %.17g; jury uses %d operations",
          participant.operations,
          participant.value,
          jury.operations);
}
