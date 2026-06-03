#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    string s = inf.readToken("[A-Z]{1,100000}", "s");
    ensuref(static_cast<int>(s.size()) == n, "s length must be n: expected %d, found %d",
            n, static_cast<int>(s.size()));
    inf.readEoln();

    inf.readEof();
}
