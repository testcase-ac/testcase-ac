#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read a single alphabet character (uppercase or lowercase)
    inf.readToken("[A-Za-z]", "c");
    // Ensure the line ends immediately after that character
    inf.readEoln();
    // No extra content in the file
    inf.readEof();

    return 0;
}
