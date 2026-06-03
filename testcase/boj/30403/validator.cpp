#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    string s = inf.readToken("[A-Za-z]{1,100}", "S");
    ensuref(static_cast<int>(s.size()) == n, "S length must equal N: N=%d, len=%d", n,
            static_cast<int>(s.size()));
    inf.readEoln();

    inf.readEof();
}
