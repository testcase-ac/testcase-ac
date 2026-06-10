#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 10000000, "N");
    inf.readEoln();

    string x = inf.readToken("[01]{2,10000000}", "X");
    ensuref((int)x.size() == n, "X length must be N: expected %d, got %d", n, (int)x.size());
    ensuref(x[0] == '1', "X must not start with 0");
    inf.readEoln();

    inf.readEof();
}
