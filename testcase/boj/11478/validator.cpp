#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the input string S: must consist of 1 to 1000 lowercase letters.
    inf.readLine("[a-z]{1,1000}", "S");

    // Exactly EOF after the single line.
    inf.readEof();
}
