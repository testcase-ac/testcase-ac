#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 2000, "m");
    inf.readEoln();

    string s = inf.readToken("[IO]{1,2000}", "s");
    inf.readEoln();
    string t = inf.readToken("[IO]{1,2000}", "t");
    inf.readEoln();

    ensuref((int)s.size() == n, "s length is %d, expected n=%d", (int)s.size(), n);
    ensuref((int)t.size() == m, "t length is %d, expected m=%d", (int)t.size(), m);

    inf.readEof();
}
