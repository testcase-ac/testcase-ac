#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the input string: must consist of 1 to 2500 uppercase letters.
    inf.readToken("[A-Z]{1,2500}", "S");
    inf.readEoln();
    inf.readEof();

    return 0;
}
