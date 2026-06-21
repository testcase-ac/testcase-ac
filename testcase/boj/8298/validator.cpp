#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 1000000, "n");
    inf.readSpace();
    inf.readInt(2, n - 1, "k");
    inf.readEoln();

    inf.readToken("[OR]{" + to_string(n) + "}", "tosses");
    inf.readEoln();

    inf.readEof();
    return 0;
}
