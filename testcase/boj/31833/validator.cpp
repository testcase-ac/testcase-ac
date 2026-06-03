#include "testlib.h"

#include <vector>

using namespace std;

static void readArrayLine(int n, const char* name) {
    vector<int> values = inf.readInts(n, 1, 99, name);
    (void)values;
    inf.readEoln();
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 9, "N");
    inf.readEoln();

    readArrayLine(n, "A_i");
    readArrayLine(n, "B_i");

    inf.readEof();
}
