#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: Jaehwan's maximum "aah" he can produce.
    // It must be of the form a{0,999}h: zero to 999 'a's, then exactly one 'h'.
    inf.readLine("a{0,999}h", "s1");

    // Second line: doctor's required "aah".
    // Same format: a{0,999}h.
    inf.readLine("a{0,999}h", "s2");

    // No extra characters after the two lines.
    inf.readEof();

    return 0;
}
