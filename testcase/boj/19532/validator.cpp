#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the six coefficients/values a, b, c, d, e, f
    int a = inf.readInt(-999, 999, "a");
    inf.readSpace();
    int b = inf.readInt(-999, 999, "b");
    inf.readSpace();
    int c = inf.readInt(-999, 999, "c");
    inf.readSpace();
    int d = inf.readInt(-999, 999, "d");
    inf.readSpace();
    int ee = inf.readInt(-999, 999, "e"); // named ee to avoid shadowing
    inf.readSpace();
    int f = inf.readInt(-999, 999, "f");
    inf.readEoln();

    // Compute determinant
    long long det = 1LL * a * ee - 1LL * b * d;
    ensuref(det != 0,
            "Determinant is zero; no unique solution (det = %lld)", det);

    // Compute numerators for Cramer's rule
    long long numX = 1LL * c * ee - 1LL * b * f;
    long long numY = 1LL * a * f - 1LL * c * d;

    // Check that solution is integral
    ensuref(numX % det == 0,
            "Numerator for x (%lld) is not divisible by det (%lld)", numX, det);
    ensuref(numY % det == 0,
            "Numerator for y (%lld) is not divisible by det (%lld)", numY, det);

    // Compute x, y and validate their ranges
    long long x = numX / det;
    long long y = numY / det;
    ensuref(-999 <= x && x <= 999,
            "Computed x = %lld is out of allowed range [-999,999]", x);
    ensuref(-999 <= y && y <= 999,
            "Computed y = %lld is out of allowed range [-999,999]", y);

    inf.readEof();
    return 0;
}
