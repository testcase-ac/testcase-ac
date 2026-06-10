#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 3000, "M");
    inf.readEoln();

    string s = inf.readToken("[ACGT]{1,3000}", "S");
    inf.readEoln();

    ensuref(m <= (int)s.size(), "M must not exceed |S|: M=%d, |S|=%d", m, (int)s.size());

    inf.readEof();
}
