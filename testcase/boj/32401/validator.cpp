#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100, "N");
    inf.readEoln();

    string s = inf.readToken("[A-Z]{3,100}", "S");
    ensuref((int)s.size() == n, "S length must be N: expected %d, found %d", n,
            (int)s.size());
    inf.readEoln();

    inf.readEof();
}
