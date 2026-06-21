#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2500, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    string s = inf.readToken("[0-9]{1,2500}", "S");
    ensuref((int)s.size() == n, "S length must be N: expected %d, got %d", n, (int)s.size());
    inf.readEoln();

    inf.readEof();
}
