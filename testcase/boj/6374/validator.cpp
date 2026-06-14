#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int i = 0; i < n * n; ++i) {
        inf.skipBlanks();
        inf.readInt(-127, 127, "a_" + to_string(i + 1));
    }

    inf.skipBlanks();
    inf.readEof();
}
