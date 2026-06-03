#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "N");
    inf.readEoln();

    string s = inf.readToken("[A-Z]{2,100}", "S");
    ensuref((int)s.size() == n, "S length must be N: expected %d, got %d", n, (int)s.size());
    inf.readEoln();
    inf.readEof();
}
