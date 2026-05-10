#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read G (natural number <= 100,000)
    int G = inf.readInt(1, 100000, "G");
    inf.readEoln();

    inf.readEof();
    return 0;
}
