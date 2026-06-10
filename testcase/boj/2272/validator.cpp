#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    inf.readInt(0, 1000000000, "M");
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        inf.readInt(0, 1, "lamp_i");
        inf.readEoln();
    }

    inf.readEof();
}
