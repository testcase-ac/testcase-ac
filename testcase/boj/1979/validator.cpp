#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k on the first line
    int n = inf.readInt(1, 9, "n");
    inf.readSpace();
    int k = inf.readInt(1, 9, "k");
    inf.readEoln();
    inf.readEof();

    return 0;
}
