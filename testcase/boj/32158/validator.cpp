#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    string s = inf.readToken("[A-Z]{1,100}", "s");
    inf.readEoln();

    ensuref((int)s.size() == n, "length of s must equal n: n=%d, |s|=%d", n, (int)s.size());

    inf.readEof();
}
