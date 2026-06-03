#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 100, "score");
    inf.readEoln();
    inf.readEof();
    return 0;
}
