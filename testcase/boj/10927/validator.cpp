#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single line with S: consists of [A-Z][a-z][0-9], length 0..50
    // The statement doesn't forbid empty string, only says "length at most 50".
    string s = inf.readLine("[A-Za-z0-9]{0,50}", "S");

    inf.readEof();
}
