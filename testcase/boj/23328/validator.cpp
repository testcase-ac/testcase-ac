#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    char b = inf.readToken("[A-Z]", "B")[0];
    inf.readEoln();

    string s = inf.readToken("[A-Za-z]{1,100000}", "S");
    inf.readEoln();

    ensuref((int)s.size() == n, "S length must be N: expected %d, got %d", n, (int)s.size());
    ensuref(s.find(b) != string::npos, "S must contain at least one exploding bomb %c", b);

    inf.readEof();
}
