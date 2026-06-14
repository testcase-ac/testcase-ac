#include "testlib.h"

#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int l = inf.readInt(1, 200000, "L");
    inf.readSpace();
    inf.readInt(1, 200000, "N");
    inf.readEoln();

    string s = inf.readToken("[a-z]{1,200000}", "S");
    inf.readEoln();

    ensuref((int)s.size() == l, "S length must be L: expected %d, got %d",
            l, (int)s.size());

    inf.readEof();
}
