#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = inf.readInt(1, 100, "C");
    inf.readEoln();

    for (int i = 0; i < c; ++i) {
        inf.readInt(-1000, 1000, "V");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
