#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: number of unit squares
    inf.readInt(1, 10000, "n");
    // Ensure exactly one newline after the number
    inf.readEoln();
    // Ensure no extra data
    inf.readEof();

    return 0;
}
