#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[a-z]{2,1000000}", "s");
    ensuref(s.size() % 2 == 0, "s length must be even, got %d", (int)s.size());
    inf.readEoln();
    inf.readEof();
}
