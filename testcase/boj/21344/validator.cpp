#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    vector<int> t = inf.readInts(n, -100000, 100000, "t_i");
    inf.readEoln();

    inf.readEof();
}
