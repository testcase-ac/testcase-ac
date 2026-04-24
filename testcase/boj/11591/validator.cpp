#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read the array of prices a_i
    vector<long long> a = inf.readLongs(N, 0LL, 1000000000LL, "a_i");
    inf.readEoln();

    // Read P
    long long P = inf.readLong(0LL, 1000000000LL, "P");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
