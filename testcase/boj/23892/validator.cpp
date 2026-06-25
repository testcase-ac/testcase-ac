#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 100000000000000LL, "N");
    inf.readSpace();
    inf.readLong(1LL, 100000000000000LL, "K");
    inf.readEoln();

    string initial = inf.readToken("[()]{1,100000}", "S_initial");
    inf.readSpace();
    inf.readInt(1, 1000000000, "P_initial");
    inf.readEoln();

    string drink = inf.readToken("[()]{1,100000}", "S_drink");
    inf.readSpace();
    inf.readInt(1, 1000000000, "P_drink");
    inf.readEoln();

    inf.readEof();
}
