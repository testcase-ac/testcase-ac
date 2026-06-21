#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(0, n, "M");
    inf.readEoln();

    string s = inf.readToken("[.X]{1,200000}", "S");
    inf.readEoln();
    inf.readEof();

    ensuref((int)s.size() == n, "S length must be N: expected %d, found %d", n, (int)s.size());
    int dots = (int)count(s.begin(), s.end(), '.');
    ensuref(m <= dots, "M must be at most the number of dots: M=%d, dots=%d", m, dots);
}
