#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the hex string line: must be 1 to 6 characters, each 0-9 or A-F, no extra spaces
    inf.readLine("[0-9A-F]{1,6}", "hex");

    // Ensure there's nothing else in the file
    inf.readEof();
    return 0;
}
