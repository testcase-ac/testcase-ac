#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    // Read the input string S: length 1 to 10, only lowercase letters.
    inf.readToken("[a-z]{1,10}", "S");
    inf.readEoln();
    inf.readEof();

    return 0;
}
