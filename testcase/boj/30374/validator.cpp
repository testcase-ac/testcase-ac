#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "n");
    inf.readEoln();

    string s = inf.readToken("[()]{1,300000}", "s");
    ensuref((int)s.size() == n, "s length must be n: expected %d, found %d", n, (int)s.size());
    inf.readEoln();

    inf.readLongs(n, -1000000000LL, 1000000000LL, "c_i");
    inf.readEoln();

    inf.readEof();
}
