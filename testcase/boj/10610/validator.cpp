#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the number N as a single token of digits
    string N = inf.readToken("[0-9]+", "N");
    // Check length constraint
    ensuref((int)N.size() <= 100000,
            "The length of N must be at most 100000, but got %d", (int)N.size());
    // Leading zero is forbidden since N is a positive integer and must not start with '0'
    ensuref(N[0] != '0',
            "N must not start with '0', but got N = \"%s\"", N.c_str());

    // After the number, there must be exactly one newline
    inf.readEoln();
    // And then EOF immediately
    inf.readEof();

    return 0;
}
