#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readToken("[DP]", "C");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
