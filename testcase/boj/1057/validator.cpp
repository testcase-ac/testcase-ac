#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of participants N
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    // Read Kim's number
    int kim = inf.readInt(1, N, "kim");
    inf.readSpace();
    // Read Lee's number
    int lee = inf.readInt(1, N, "lee");
    inf.readEoln();

    // They must be distinct participants
    ensuref(kim != lee,
            "kim and lee must be distinct, but both are %d",
            kim);

    // No extra input
    inf.readEof();
    return 0;
}
