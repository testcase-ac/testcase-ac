#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first parentheses string A
    string A = inf.readToken("[()]{1,200000}", "A");
    inf.readEoln();

    // Read second parentheses string B
    string B = inf.readToken("[()]{1,200000}", "B");
    inf.readEoln();

    inf.readEof();
    return 0;
}
