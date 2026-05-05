#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(0, 50, "n");
    inf.readEoln();

    inf.readEof();
}
