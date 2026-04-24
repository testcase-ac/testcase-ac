#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: the number of integers, 1 ≤ N ≤ 50
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Read the array of N integers, each in [0,1000]
    vector<int> a = inf.readInts(N, 0, 1000, "a_i");
    inf.readEoln();

    // Ensure no extra data
    inf.readEof();
    return 0;
}
