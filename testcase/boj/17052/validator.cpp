#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    string s = inf.readToken("[0-9x]{1,100}", "S");
    inf.readEoln();

    ensuref((int)s.size() == n, "S length is %d, expected %d", (int)s.size(), n);
    ensuref(count(s.begin(), s.end(), 'x') == 1, "S must contain exactly one x");

    inf.readEof();
}
