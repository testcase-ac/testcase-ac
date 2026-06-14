#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 400, "N");
    inf.readEoln();

    string s = inf.readToken("[RGY]{1,400}", "S");
    inf.readEoln();
    ensuref(int(s.size()) == n, "S length is %d, expected %d", int(s.size()), n);

    inf.readEof();
}
