#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "n");
    inf.readEoln();

    string s = inf.readToken("[a-zA-Z]{1,300000}", "S");
    inf.readEoln();
    ensuref((int)s.size() == n, "S length must equal n: length=%d, n=%d",
            (int)s.size(), n);

    inf.readEof();
}
