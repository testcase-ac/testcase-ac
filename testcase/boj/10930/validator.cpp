#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the input string S: must be 1 to 50 characters, only [A-Za-z0-9]
    inf.readToken("[A-Za-z0-9]{1,50}", "S");
    inf.readEoln();

    // No extra content
    inf.readEof();
    return 0;
}
