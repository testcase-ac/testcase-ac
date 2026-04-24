#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the input string S: only lowercase letters, length between 1 and 5000.
    inf.readLine("[a-z]{1,5000}", "S");

    // After the single line, there must be EOF immediately.
    inf.readEof();
    return 0;
}
