#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 200000, "n");
    inf.readEoln();

    // Read array a[1..n]
    vector<long long> a = inf.readLongs(n, -1000000000LL, 1000000000LL, "a_i");
    inf.readEoln();

    // No more data
    inf.readEof();
    return 0;
}
