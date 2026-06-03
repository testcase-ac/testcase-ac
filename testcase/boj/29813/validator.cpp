#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();
    ensuref(n % 2 == 1, "N must be odd: %d", n);

    for (int i = 0; i < n; ++i) {
        string initials = inf.readToken("[A-Z]{1,3}", "initials");
        inf.readSpace();
        int lastTwoDigits = inf.readInt(1, 99, "last_two_digits");
        inf.readEoln();
        (void)initials;
        (void)lastTwoDigits;
    }

    inf.readEof();
}
