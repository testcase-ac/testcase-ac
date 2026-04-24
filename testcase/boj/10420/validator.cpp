#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer N: 1 ≤ N ≤ 10000
    inf.readInt(1, 10000, "N");
    // Must end the line after N
    inf.readEoln();
    // No more content
    inf.readEof();

    return 0;
}
