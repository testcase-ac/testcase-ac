#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read and validate N
    int N = inf.readInt(1, 20, "N");
    inf.readEoln();

    // Read and validate the bit strings
    // Each must be 1 to 1000 characters of '0' or '1'
    string before = inf.readLine("[01]{1,1000}", "before_bits");
    string after  = inf.readLine("[01]{1,1000}", "after_bits");

    // Ensure the two strings have the same length
    ensuref(before.size() == after.size(),
            "Length mismatch: before_bits has length %d, after_bits has length %d",
            (int)before.size(), (int)after.size());

    // No extra data
    inf.readEof();
    return 0;
}
