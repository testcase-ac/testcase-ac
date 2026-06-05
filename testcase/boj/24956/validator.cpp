#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    string s = inf.readToken("[A-Z]{1,200000}", "S");
    inf.readEoln();
    ensuref((int)s.size() == n, "S length must equal N: expected %d, got %d", n, (int)s.size());

    inf.readEof();
}
