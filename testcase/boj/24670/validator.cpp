#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    // Read m
    int m = inf.readInt(1, 100, "m");
    inf.readSpace();
    // Read k
    int k = inf.readInt(1, 100, "k");
    inf.readEoln();

    inf.readEof();
}
