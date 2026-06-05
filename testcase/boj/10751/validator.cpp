#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: the statement only gives N <= 100000; require a nonempty inscription.
    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    string s = inf.readToken("[COW]{1,100000}", "s");
    ensuref((int)s.size() == n, "s length must equal N: N=%d, length=%d", n, (int)s.size());
    inf.readEoln();
    inf.readEof();
}
