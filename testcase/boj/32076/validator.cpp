#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The input is exactly a 3x3 grid of letters A, B, or C.
    // Each of the three lines must consist of exactly 3 characters in [ABC], with no extra spaces.
    for (int i = 0; i < 3; i++) {
        inf.readLine("[ABC]{3}", "row");
    }

    // No extra lines or characters after the 3 lines.
    inf.readEof();
    return 0;
}
