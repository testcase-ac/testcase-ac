#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read three natural numbers <= 100
    int a = inf.readInt(1, 100, "a");
    inf.readSpace();
    int b = inf.readInt(1, 100, "b");
    inf.readSpace();
    int c = inf.readInt(1, 100, "c");
    inf.readEoln();

    // Check that at least one valid equation exists:
    // Either a op b = c, or a = b op c, with op in {+,-,*,/} and exact integer division.
    bool ok = false;
    if (a + b == c) ok = true;
    if (a - b == c) ok = true;
    if (a * b == c) ok = true;
    if (b != 0 && a % b == 0 && a / b == c) ok = true;
    if (b + c == a) ok = true;
    if (b - c == a) ok = true;
    if ((long long)b * c == a) ok = true;
    if (c != 0 && b % c == 0 && b / c == a) ok = true;

    ensuref(ok, "No valid expression exists for input (%d, %d, %d)", a, b, c);

    inf.readEof();
    return 0;
}
