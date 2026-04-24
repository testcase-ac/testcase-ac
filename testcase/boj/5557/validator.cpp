#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of integers
    int N = inf.readInt(3, 100, "N");
    inf.readEoln();

    // Read the N integers, each between 0 and 9
    vector<int> a = inf.readInts(N, 0, 9, "a_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
