#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int i = 1; i <= 3; ++i) {
        inf.readInt(0, 9, format("digit_%d", i).c_str());
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
