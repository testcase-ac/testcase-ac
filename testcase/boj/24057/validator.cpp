#include "testlib.h"

#include <numeric>

using namespace std;

struct Value {
    int a;
    int b;
    int c;
    int d;
};

bool isSquareFreeGreaterThanOne(int x) {
    for (int p = 2; p * p <= x; ++p) {
        if (x % (p * p) == 0) {
            return false;
        }
    }
    return true;
}

Value readValue(const char* prefix) {
    Value v;
    v.a = inf.readInt(1, 1000, format("%s_a", prefix));
    inf.readSpace();
    v.b = inf.readInt(-1000, 1000, format("%s_b", prefix));
    inf.readSpace();
    v.c = inf.readInt(-1000, 1000, format("%s_c", prefix));
    inf.readSpace();
    v.d = inf.readInt(0, 1000, format("%s_d", prefix));
    inf.readEoln();

    ensuref(v.d != 1, "%s_d must not be 1", prefix);
    ensuref(gcd(gcd(v.a, abs(v.b)), abs(v.c)) == 1,
            "gcd(%s_a, %s_b, %s_c) must be 1", prefix, prefix, prefix);
    ensuref((v.c == 0) == (v.d == 0),
            "%s_c == 0 must hold if and only if %s_d == 0", prefix, prefix);
    if (v.d > 0) {
        ensuref(isSquareFreeGreaterThanOne(v.d),
                "%s_d must not have a square divisor greater than 1", prefix);
    }
    return v;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    Value a = readValue("A");
    Value b = readValue("B");

    ensuref(a.d == b.d, "A_d and B_d must be equal");
    if (b.d == 0) {
        ensuref(b.b != 0, "B must not be zero");
    }

    inf.readEof();
}
