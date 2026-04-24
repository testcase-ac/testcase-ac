#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the first word: only lowercase letters, length between 1 and 1000
    inf.readLine("[a-z]{1,1000}", "first_word");

    // Read the second word: only lowercase letters, length between 1 and 1000
    inf.readLine("[a-z]{1,1000}", "second_word");

    // No extra data
    inf.readEof();

    return 0;
}
