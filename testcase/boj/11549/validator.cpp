#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 4, "T");
    inf.readEoln();

    inf.readInts(5, 1, 4, "answer");
    inf.readEoln();

    inf.readEof();
    return 0;
}
