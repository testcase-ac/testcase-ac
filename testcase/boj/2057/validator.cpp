#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N is a single integer, range: 0 ≤ N ≤ 1e18
    long long N = inf.readLong(0LL, 1000000000000000000LL, "N");
    inf.readEoln();

    // Problem does NOT state anything like "answer always exists",
    // so no need for extra global property checks beyond range.

    inf.readEof();
}
