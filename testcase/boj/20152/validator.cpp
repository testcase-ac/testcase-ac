#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int H = inf.readInt(0, 30, "H");
    inf.readSpace();
    int N = inf.readInt(0, 30, "N");
    inf.readEoln();

    inf.readEof();
    return 0;
}
