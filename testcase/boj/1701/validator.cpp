#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the input string: must consist of 1 to 5000 lowercase letters
    inf.readLine("[a-z]{1,5000}", "s");

    // Ensure exactly one newline at end and then EOF
    inf.readEof();
    return 0;
}
