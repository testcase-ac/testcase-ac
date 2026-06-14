#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 99, "N");
    inf.readEoln();
    ensuref(n % 2 == 1, "N must be odd: %d", n);

    string s = inf.readToken("[A-Z]{1,99}", "S");
    inf.readEoln();
    ensuref((int)s.size() == n, "S length must be N: length=%d, N=%d",
            (int)s.size(), n);

    inf.readEof();
}
