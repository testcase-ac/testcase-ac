#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(1LL, 1000000000000000000LL, "N");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "M");
    inf.readEoln();

    string x = inf.readToken("[01]{1,200000}", "X");
    ensuref((int)x.size() == m, "X must have exactly M digits: M=%d, length=%d",
            m, (int)x.size());
    inf.readEoln();

    inf.readEof();
}
