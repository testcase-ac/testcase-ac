#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: number of elements in the heap
    int n = inf.readInt(1, 100000, "n");
    // After the integer, there must be exactly one end-of-line
    inf.readEoln();
    // No more content after the single line
    inf.readEof();

    return 0;
}
