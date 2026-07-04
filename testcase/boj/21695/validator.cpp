#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    string row = inf.readToken("[ab]{1,1000000}", "row");
    ensuref((int)row.size() == n, "row length must be n: expected %d, found %d", n, (int)row.size());
    inf.readEoln();
    inf.readEof();
}
