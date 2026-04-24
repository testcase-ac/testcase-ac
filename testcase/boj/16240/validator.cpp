#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 50000, "N");
    inf.readEoln();

    // Function to read a line of N elements
    auto readArray = [&](const string &name) {
        for (int i = 0; i < N; i++) {
            // Each element is either a variable: 1-10 lowercase letters
            // or a positive integer in [1,999] without leading zeros
            inf.readToken("[a-z]{1,10}|[1-9][0-9]{0,2}", name.c_str());
            if (i + 1 < N)
                inf.readSpace();
            else
                inf.readEoln();
        }
    };

    // Read both arrays
    readArray("a_i");
    readArray("b_i");

    inf.readEof();
    return 0;
}
