#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single line: the string
    string s = inf.readToken("[a-z]{1,50}", "s");
    inf.readEoln();

    // No more input
    inf.readEof();
}
