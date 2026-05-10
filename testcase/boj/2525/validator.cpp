#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the current time: hours A and minutes B
    int A = inf.readInt(0, 23, "A");
    inf.readSpace();
    int B = inf.readInt(0, 59, "B");
    inf.readEoln();

    // Read the cooking duration C in minutes
    int C = inf.readInt(0, 1000, "C");
    inf.readEoln();

    // Ensure no extra data
    inf.readEof();
    return 0;
}
