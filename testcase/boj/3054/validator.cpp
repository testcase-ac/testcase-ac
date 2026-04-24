#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the word: uppercase letters only, length between 1 and 15
    inf.readToken("[A-Z]{1,15}", "word");
    inf.readEoln();
    inf.readEof();

    return 0;
}
