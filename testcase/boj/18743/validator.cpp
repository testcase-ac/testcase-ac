#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(2, 1000000, "n");
    inf.readSpace();
    int k = inf.readInt(0, 100, "k");
    inf.readEoln();

    inf.readEof();
}
