#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int l = inf.readInt(1, 1000000, "L");
    inf.readEoln();

    string s = inf.readToken("[a-z]{1,1000000}", "S");
    ensuref((int)s.size() == l, "S length is %d, expected %d", (int)s.size(), l);
    inf.readEoln();

    inf.readEof();
}
