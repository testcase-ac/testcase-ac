#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read S: a natural number, 1 ≤ S ≤ 4,294,967,295
    long long S = inf.readLong(1LL, 4294967295LL, "S");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
