#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 10000, "A");
    inf.readSpace();
    inf.readInt(1, 10000, "B");
    inf.readEoln();
    inf.readEof();
}
