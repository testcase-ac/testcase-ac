#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 20000, "N");
    inf.readEoln();

    string mascot = inf.readToken("annyong|induck", "mascot");
    inf.readEoln();

    inf.readInt(1, n, "K");
    inf.readEoln();
    inf.readEof();
}
