#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 200000, "n");
    inf.readEoln();

    // Read the sequence s_1 ... s_n
    vector<long long> s = inf.readLongs(n, -10000000LL, 10000000LL, "s_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
