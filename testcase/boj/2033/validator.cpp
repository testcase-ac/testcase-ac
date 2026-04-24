#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read single integer N: 0 ≤ N ≤ 99,999,999
    long long N = inf.readLong(0LL, 99999999LL, "N");
    inf.readEoln();

    inf.readEof();
    return 0;
}
