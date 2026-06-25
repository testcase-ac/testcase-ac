#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "N");
    inf.readEoln();

    int count = 1 << n;
    for (int i = 0; i < count; ++i) {
        inf.readInt(1, 1000000000, "a_i");
        if (i + 1 == count) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    inf.readEof();
    return 0;
}
