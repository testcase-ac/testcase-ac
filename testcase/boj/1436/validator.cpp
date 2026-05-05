#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: the index of the movie title number
    inf.readInt(1, 10000, "N");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
