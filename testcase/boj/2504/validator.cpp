#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Read the bracket string: only characters '(', ')', '[', ']',
    // length between 1 and 30 inclusive.
    inf.readLine("[()\\[\\]]{1,30}", "s");
    // No extra lines or characters after this.
    inf.readEof();
    return 0;
}
