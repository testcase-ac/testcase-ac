#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        string s = inf.readToken("[a-z]{1,50}", "S_i");
        inf.readEoln();
    }

    inf.readEof();
}
