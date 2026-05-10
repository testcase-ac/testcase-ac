#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(3, 100000, "n");
    inf.readSpace();
    int k = inf.readInt(3, n, "k");
    inf.readEoln();

    // Read array a
    vector<int> a = inf.readInts(n, 0, 50000, "a_i");
    inf.readEoln();

    inf.readEof();
}
