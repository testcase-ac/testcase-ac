#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "n");
    inf.readEoln();

    string s = inf.readToken("[a-z]{1,5000}", "s");
    inf.readEoln();
    string t = inf.readToken("[a-z]{1,5000}", "t");
    inf.readEoln();

    ensuref(static_cast<int>(s.size()) == n, "s length must be n: expected %d, found %d", n,
            static_cast<int>(s.size()));
    ensuref(static_cast<int>(t.size()) == n, "t length must be n: expected %d, found %d", n,
            static_cast<int>(t.size()));

    inf.readEof();
}
