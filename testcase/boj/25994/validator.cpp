#include "testlib.h"

#include <cstdlib>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 2000, "c");
    inf.readSpace();
    inf.readLong(0LL, 1000000000LL, "t");
    inf.readSpace();
    inf.readLong(0LL, 1000000000LL, "r");
    inf.readEoln();

    string p = inf.readToken("0\\.[0-9]{1,10}", "p");
    double value = strtod(p.c_str(), nullptr);
    ensuref(0.001 <= value && value <= 0.999,
            "p must be between 0.001 and 0.999, got %s", p.c_str());
    inf.readEoln();

    inf.readEof();
}
