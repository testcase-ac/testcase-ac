#include "testlib.h"
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 3000, "N");
    inf.readEoln();

    string s = inf.readToken("[()]{2,6000}", "S");
    inf.readEoln();
    ensuref((int)s.size() == 2 * n, "S length must be 2N: got %d for N=%d", (int)s.size(), n);

    int openCount = count(s.begin(), s.end(), '(');
    ensuref(openCount == n, "S must contain exactly N open brackets: got %d for N=%d", openCount, n);

    inf.readEof();
    return 0;
}
