#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string n = inf.readToken("[0-9A-F]{1,250}", "N");
    ensuref(n[0] != '0', "N must not have leading zero");
    inf.readEoln();

    inf.readInt(0, 1000, "K");
    inf.readEoln();

    inf.readEof();
}
