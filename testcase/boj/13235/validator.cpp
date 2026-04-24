#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the input word: must be 1 to 20 lowercase letters
    inf.readLine("[a-z]{1,20}", "word");

    // Ensure no extra data
    inf.readEof();
    return 0;
}
