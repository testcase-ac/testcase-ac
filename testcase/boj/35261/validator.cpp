#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 100, "N");
    inf.readEoln();

    std::string s = inf.readToken("[a-z]{5,100}", "S");
    ensuref((int)s.size() == n, "S length must be N: expected %d, got %d", n, (int)s.size());
    inf.readEoln();

    inf.readEof();
}
