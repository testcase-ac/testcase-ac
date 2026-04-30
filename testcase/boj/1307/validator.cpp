#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(3, 300, "N");
    inf.readEoln();

    // No further input
    inf.readEof();
}
