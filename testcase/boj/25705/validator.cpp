#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    string wheel = inf.readToken("[a-z]{1,100}", "wheel");
    ensuref((int)wheel.size() == n, "wheel length %d does not match n %d",
            (int)wheel.size(), n);
    inf.readEoln();

    int m = inf.readInt(1, 100, "m");
    inf.readEoln();

    string s = inf.readToken("[a-z]{1,100}", "s");
    ensuref((int)s.size() == m, "s length %d does not match m %d",
            (int)s.size(), m);
    inf.readEoln();

    inf.readEof();
}
