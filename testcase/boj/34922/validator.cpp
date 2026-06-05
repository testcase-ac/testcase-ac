#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int w = inf.readInt(1, 100, "w");
    inf.readSpace();
    int h = inf.readInt(1, 100, "h");
    inf.readEoln();

    inf.readInt(1, min(w, h), "r");
    inf.readEoln();

    inf.readEof();
}
