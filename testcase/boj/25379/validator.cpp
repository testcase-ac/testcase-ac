#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read the array A of length N
    inf.readLongs(N, 0LL, 2000000000LL, "A_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
