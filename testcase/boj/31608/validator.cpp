#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    string s = inf.readToken("[a-z]{1,100}", "S");
    inf.readEoln();
    string t = inf.readToken("[a-z]{1,100}", "T");
    inf.readEoln();

    ensuref((int)s.size() == n, "S length must be N: expected %d, got %d", n, (int)s.size());
    ensuref((int)t.size() == n, "T length must be N: expected %d, got %d", n, (int)t.size());

    inf.readEof();
}
