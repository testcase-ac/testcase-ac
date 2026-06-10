#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    string s = inf.readToken("[A-E]{1,100}", "S");
    ensuref((int)s.size() == n, "S length must be N: N=%d, |S|=%d", n, (int)s.size());
    inf.readEoln();

    inf.readEof();
}
