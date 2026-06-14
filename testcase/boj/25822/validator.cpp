#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string c = inf.readToken("[0-5][.][0-9][0-9]", "c");
    int cents = (c[0] - '0') * 100 + (c[2] - '0') * 10 + (c[3] - '0');
    ensuref(cents <= 500, "c must be at most 5.00, got %s", c.c_str());
    inf.readEoln();

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    vector<int> solved = inf.readInts(n, 0, 24, "solved_i");
    inf.readEoln();

    inf.readEof();
}
