#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer N: 1 ≤ N ≤ 4,000,000
    inf.readInt(1, 4000000, "N");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
