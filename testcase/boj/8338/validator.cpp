#include "testlib.h"

#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 1000000, "m");
    inf.readSpace();
    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    string s = inf.readToken("[01]{1,1000000}", "s");
    ensuref((int)s.size() == m, "s length must be m: expected %d, found %d", m, (int)s.size());
    inf.readEoln();
    inf.readEof();
}
