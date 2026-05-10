#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 2000, "N");
    inf.readEoln();

    // Read N lines, each with a single uppercase letter
    for (int i = 0; i < N; ++i) {
        string ch = inf.readToken("[A-Z]", "S_i");
        inf.readEoln();
        ensuref(ch.size() == 1, "Line %d: Each line must contain exactly one uppercase letter, got: '%s'", i+2, ch.c_str());
    }

    inf.readEof();
}
