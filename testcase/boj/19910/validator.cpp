#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "n");
    inf.readEoln();

    string s = inf.readToken("[01]{1,500000}", "s");
    inf.readEoln();

    ensuref((int)s.size() == n, "s length must equal n: length=%d n=%d",
            (int)s.size(), n);
    ensuref(count(s.begin(), s.end(), '1') >= 1, "s must contain at least one 1");

    inf.readEof();
}
