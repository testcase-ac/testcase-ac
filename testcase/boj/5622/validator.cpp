#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The input is a single uppercase word of length between 2 and 15.
    inf.readToken("[A-Z]{2,15}", "word");
    inf.readEoln();
    inf.readEof();
    return 0;
}
