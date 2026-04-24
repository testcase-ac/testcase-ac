#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: 2 ≤ N ≤ 10^5
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // Read the array of N integers, each between -1e9 and 1e9
    inf.readLongs(N, -1000000000LL, 1000000000LL, "a_i");
    inf.readEoln();

    // No more data allowed
    inf.readEof();
    return 0;
}
