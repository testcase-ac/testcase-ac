#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    std::string s = inf.readToken("[()]{1,200000}", "S");
    ensuref((int)s.size() == n, "S length must equal N: N=%d, length=%d", n, (int)s.size());
    inf.readEoln();
    inf.readEof();
}
