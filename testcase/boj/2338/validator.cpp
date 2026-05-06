#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A: optional '-' followed by 1 to 1000 digits, no extra characters
    inf.readLine("-?[0-9]{1,1000}", "A");
    // Read B: same format
    inf.readLine("-?[0-9]{1,1000}", "B");

    // No more input
    inf.readEof();
    return 0;
}
