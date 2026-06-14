#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readEoln();

    string s = inf.readToken("[a-z]{1,500000}", "S");
    ensuref(static_cast<int>(s.size()) == n,
            "S length must equal N: N=%d, |S|=%d", n, static_cast<int>(s.size()));
    inf.readEoln();

    inf.readEof();
}
