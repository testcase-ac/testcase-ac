#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the document: only lowercase letters and spaces, length 1 to 2500
    inf.readLine("[a-z\\ ]{1,2500}", "document");
    // Read the pattern: only lowercase letters and spaces, length 1 to 50
    inf.readLine("[a-z\\ ]{1,50}", "pattern");

    inf.readEof();
    return 0;
}
