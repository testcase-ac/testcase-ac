#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 200000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n / 3, "K");
    inf.readEoln();

    string s = inf.readToken("[JOI]{3,200000}", "S");
    ensuref((int)s.size() == n, "S length must be N: expected %d, got %d", n, (int)s.size());
    inf.readEoln();

    inf.readEof();
}
