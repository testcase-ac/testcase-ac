#include "testlib.h"

#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string n = inf.readToken("[0-9]{4}", "N");
    inf.readSpace();
    int m = inf.readInt(0, 100, "M");
    inf.readEoln();
    inf.readEof();

    ensuref(!n.empty(), "N must be a four-digit token");
    (void)m;
}
