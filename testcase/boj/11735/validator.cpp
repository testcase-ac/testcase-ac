#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        string type = inf.readToken("R|C", "type");
        inf.readSpace();
        inf.readInt(1, n, "index");
        inf.readEoln();
    }

    inf.readEof();
}
