#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 100000, "N");
    inf.readEoln();

    string s = inf.readToken("[A-Z]{5,100000}", "S");
    ensuref((int)s.size() == n, "S length must equal N: N=%d, len=%d", n, (int)s.size());
    inf.readEoln();

    inf.readEof();
}
