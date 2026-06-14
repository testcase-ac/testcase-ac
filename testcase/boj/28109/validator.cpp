#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    inf.readInt(1, 1000000000, "K");
    inf.readEoln();

    string s = inf.readToken("[A-Z]{1,100000}", "S");
    ensuref((int)s.size() == n, "S length must be N: expected %d, got %d", n, (int)s.size());
    inf.readEoln();

    inf.readEof();
}
