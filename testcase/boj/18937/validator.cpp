#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read bridge sizes A_i
    // There must be exactly N integers, each between 2 and 1e9 inclusive
    inf.readInts(N, 2, 1000000000, "A_i");
    inf.readEoln();

    // Read starting player name: must be exactly "Whiteking" or "Blackking"
    inf.readToken("Whiteking|Blackking", "starting_player");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
