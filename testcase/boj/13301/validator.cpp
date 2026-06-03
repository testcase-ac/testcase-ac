#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 80, "N");
    inf.readEoln();
    inf.readEof();
}
