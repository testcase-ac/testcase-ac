#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100000, "n");
    inf.readEoln();

    string s = inf.readToken("[RGB]{3,100000}", "s");
    ensuref((int)s.size() == n, "s length must be n: n=%d, length=%d", n, (int)s.size());
    inf.readEoln();

    inf.readEof();
}
