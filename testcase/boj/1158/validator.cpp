#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "N");
    inf.readSpace();
    inf.readInt(1, n, "K");
    inf.readEoln();

    inf.readEof();
}
