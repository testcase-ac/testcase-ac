#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "n");
    inf.readEoln();

    vector<int> rows = inf.readInts(n, 0, n, "row_count");
    inf.readEoln();

    vector<int> cols = inf.readInts(n, 0, n, "col_count");
    inf.readEoln();

    inf.readEof();
}
