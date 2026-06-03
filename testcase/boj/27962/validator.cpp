#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2000, "N");
    inf.readEoln();

    std::string s = inf.readToken("[a-z]{2,2000}", "S");
    ensuref((int)s.size() == n, "S length must be N: N=%d, length=%d", n, (int)s.size());
    inf.readEoln();

    inf.readEof();
}
