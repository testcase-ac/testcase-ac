#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single integer N: 1 ≤ N ≤ 30
    int N = inf.readInt(1, 30, "N");
    inf.readEoln();

    inf.readEof();
    return 0;
}
