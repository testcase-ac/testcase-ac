#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the string S: only lowercase letters, length between 1 and 1000
    inf.readToken("[a-z]{1,1000}", "S");
    inf.readEoln();
    
    inf.readEof();
    return 0;
}
