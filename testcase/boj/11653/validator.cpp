#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: 1 ≤ N ≤ 10,000,000
    inf.readInt(1, 10000000, "N");
    // The line must end right after N
    inf.readEoln();
    // No extra data
    inf.readEof();

    return 0;
}
