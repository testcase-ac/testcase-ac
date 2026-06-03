#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(2, 100000, "N");
    inf.readEoln();
    inf.readEof();

    return 0;
}
