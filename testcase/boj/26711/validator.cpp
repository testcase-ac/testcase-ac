#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first number a: positive integer, no leading zeros, up to 5000 digits
    string a = inf.readLine("[1-9][0-9]{0,4999}", "a");
    // Read second number b: same constraints
    string b = inf.readLine("[1-9][0-9]{0,4999}", "b");

    // After two lines there must be exactly one newline (consumed by readLine),
    // and then immediately EOF.
    inf.readEof();
    return 0;
}
