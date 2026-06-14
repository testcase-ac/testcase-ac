#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300, "N");
    inf.readSpace();
    int m = inf.readInt(1, 300, "M");
    inf.readEoln();

    string s = inf.readToken("[a-z]{1,300}", "first string");
    inf.readEoln();
    string t = inf.readToken("[a-z]{1,300}", "second string");
    inf.readEoln();

    ensuref((int)s.size() == n, "first string length is %d, expected %d",
            (int)s.size(), n);
    ensuref((int)t.size() == m, "second string length is %d, expected %d",
            (int)t.size(), m);

    inf.readEof();
}
