#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300, "N");
    inf.readSpace();
    inf.readLong(0LL, 1000000000000000000LL, "M");
    inf.readEoln();

    string s = inf.readToken("[a-z]{1,300}", "S");
    ensuref((int)s.size() == n, "S length must be N: expected %d, found %d", n, (int)s.size());
    inf.readEoln();

    inf.readEof();
}
