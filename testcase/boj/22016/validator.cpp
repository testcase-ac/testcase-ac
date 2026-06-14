#include "testlib.h"

#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    string t = inf.readToken("[joiJOI]{1,100}", "T");
    ensuref((int)t.size() == n, "T length must be N: got %d, expected %d",
            (int)t.size(), n);
    inf.readEoln();
    inf.readEof();
}
