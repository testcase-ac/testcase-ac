#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer L: 200 <= L <= 300
    int L = inf.readInt(200, 300, "L");
    inf.readEoln();

    inf.readEof();
    return 0;
}
