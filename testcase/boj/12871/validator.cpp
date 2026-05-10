#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first string s
    string s = inf.readToken("[a-z]{1,50}", "s");
    inf.readEoln();

    // Read second string t
    string t = inf.readToken("[a-z]{1,50}", "t");
    inf.readEoln();

    inf.readEof();
}
