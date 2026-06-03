#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int i = 0; i < 6; ++i) {
        inf.readInt(0, 100, "score_count");
        inf.readEoln();
    }

    inf.readEof();
}
