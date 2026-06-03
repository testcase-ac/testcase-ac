#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readEoln();

    string s = inf.readToken("[A-Z0-9]{1,50}", "S");
    inf.readEoln();
    ensuref((int)s.size() == n, "S length is %d, expected N=%d", (int)s.size(), n);

    inf.readEof();
    return 0;
}
