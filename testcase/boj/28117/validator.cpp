#include "testlib.h"

#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 80, "N");
    inf.readEoln();

    string s = inf.readToken("[a-z]{1,80}", "S");
    inf.readEoln();

    ensuref((int)s.size() == n, "S length is %d, expected %d", (int)s.size(), n);
    ensuref(s.find("int") == string::npos, "S must not contain int as a substring");

    inf.readEof();
}
