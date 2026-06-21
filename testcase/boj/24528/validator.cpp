#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    char previous = '\0';
    for (int i = 1; i <= n; ++i) {
        std::string c = inf.readToken("[a-z]", "c_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "v_i");
        inf.readEoln();

        ensuref(i == 1 || c[0] != previous,
                "adjacent compressed letters must differ at index %d", i);
        previous = c[0];
    }

    inf.readEof();
}
