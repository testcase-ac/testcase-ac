#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 300000, "N");
    inf.readSpace();
    int m = inf.readInt(4, n, "M");
    inf.readEoln();

    string s = inf.readToken("[A-Z]{" + to_string(n) + "}", "S");
    ensuref((int)s.size() == n, "S length must be N");
    (void)m;
    inf.readEoln();

    inf.readEof();
}
