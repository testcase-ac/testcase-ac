#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(380, 780, "lambda");
    inf.readEoln();
    inf.readEof();
}
