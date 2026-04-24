#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the name: only uppercase letters, length between 1 and 50
    inf.readToken("[A-Z]{1,50}", "S");
    inf.readEoln();
    inf.readEof();

    return 0;
}
