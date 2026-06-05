#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readEoln();

    inf.readLongs(n, 0LL, 1000000000LL, "exact_count");
    inf.readEoln();

    inf.readLongs(n - 1, 0LL, 1000000000LL, "adjacent_count");
    inf.readEoln();

    inf.readEof();
    return 0;
}
