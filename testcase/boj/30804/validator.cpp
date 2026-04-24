#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // Read the sequence S of length N, each in [1,9]
    vector<int> S = inf.readInts(N, 1, 9, "S_i");
    inf.readEoln();

    // No further global constraints to check
    inf.readEof();
    return 0;
}
