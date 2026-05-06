#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single word: lowercase letters only, length 1 to 100
    inf.readToken("[a-z]{1,100}", "word");
    inf.readEoln();
    inf.readEof();

    return 0;
}
