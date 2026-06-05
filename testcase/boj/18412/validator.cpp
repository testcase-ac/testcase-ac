#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200, "N");
    inf.readSpace();
    int a = inf.readInt(1, n, "A");
    inf.readSpace();
    int b = inf.readInt(a, n, "B");
    inf.readEoln();

    string s = inf.readToken("[A-Za-z]{1,200}", "S");
    ensuref(static_cast<int>(s.size()) == n, "S length must be N: expected %d, got %d",
            n, static_cast<int>(s.size()));
    inf.readEoln();

    inf.readEof();
}
