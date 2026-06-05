#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int i = 1; i <= 10; ++i) {
        string p = inf.readToken("0\\.[0-9]{1,2}|1|1\\.0|1\\.00", format("p_%d", i).c_str());
        ensuref(p != "0.0" && p != "0.00", "p_%d must be greater than 0", i);
        inf.readEoln();
    }

    inf.readEof();
}
