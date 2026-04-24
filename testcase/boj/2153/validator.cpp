#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the word: must consist of only uppercase/lowercase letters, length 1 to 20.
    string word = inf.readToken("[A-Za-z]{1,20}", "word");
    inf.readEoln();

    // No further lines; immediately EOF.
    inf.readEof();
    return 0;
}
