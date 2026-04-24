#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, the number of cards
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // No more tokens
    inf.readEof();
    return 0;
}
