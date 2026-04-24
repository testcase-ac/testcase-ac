#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single word: must be 1 to 100 lowercase letters
    inf.readToken("[a-z]{1,100}", "word");
    inf.readEoln();

    // No extra content
    inf.readEof();
    return 0;
}
