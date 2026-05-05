#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer N: 3 <= N <= 200000
    int N = inf.readInt(3, 200000, "N");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
