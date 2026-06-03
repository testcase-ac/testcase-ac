#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    vector<int> ids = inf.readInts(n, 2, 1000000, "ID");
    (void)ids;
    inf.readEoln();

    inf.readEof();
}
