#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    string s = inf.readToken("[a-z]{1,1000}", "S");
    ensuref((int)s.size() == n, "S length must equal n: n=%d, len=%d", n, (int)s.size());
    inf.readEoln();

    inf.readEof();
}
