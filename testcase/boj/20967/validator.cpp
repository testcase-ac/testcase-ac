#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the heard string: must be 1 to 100000 lowercase letters
    inf.readToken("[a-z]{1,100000}", "heard");
    inf.readEoln();
    inf.readEof();

    return 0;
}
