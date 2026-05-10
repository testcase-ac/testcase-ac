#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the only line: N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    inf.readEof();
}
