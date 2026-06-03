#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(-1000000, 1000000, "n");
    inf.readEoln();
    inf.readEof();

    return 0;
}
