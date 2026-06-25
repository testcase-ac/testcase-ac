#include "testlib.h"

#include <numeric>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int x = inf.readInt(0, 100000000, "x");
    inf.readSpace();
    int y = inf.readInt(0, 100000000, "y");
    inf.readEoln();

    bool visible = x <= 1 || y <= 1 || gcd(x, y) == 1;
    ensuref(visible, "starting point (%d, %d) cannot see the house", x, y);

    inf.readEof();
}
