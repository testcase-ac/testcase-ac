#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of exam rooms
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read the number of students in each room
    vector<int> A = inf.readInts(N, 1, 1000000, "A_i");
    inf.readEoln();

    // Read B and C
    int B = inf.readInt(1, 1000000, "B");
    inf.readSpace();
    int C = inf.readInt(1, 1000000, "C");
    inf.readEoln();

    inf.readEof();
    return 0;
}
