#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readEoln();

    string s = inf.readToken("[JOI]{2,1000}", "responsibles");
    ensuref((int)s.size() == n, "responsibles length is %d, expected %d",
            (int)s.size(), n);
    inf.readEoln();

    inf.readEof();
}
