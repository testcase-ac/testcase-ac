#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readToken("[a-z]{1,50}", "word");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
