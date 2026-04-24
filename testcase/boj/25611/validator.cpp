#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 500000, "N");
    inf.readEoln();

    // Read heights h_1 ... h_N
    vector<long long> h = inf.readLongs(N, 1LL, 1000000000LL, "h_i");
    inf.readEoln();

    // No extra content
    inf.readEof();
    return 0;
}
