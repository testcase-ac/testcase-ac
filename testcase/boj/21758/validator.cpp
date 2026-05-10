#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(3, 100000, "N");
    inf.readEoln();

    // Read array of honey amounts
    vector<int> a = inf.readInts(N, 1, 10000, "a");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
