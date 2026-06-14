#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        string w = inf.readToken("[A-Z]{1,25}", "W_i");
        inf.readEoln();
    }

    inf.readEof();
}
