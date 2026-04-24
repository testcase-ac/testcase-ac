#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read S, A, B: each is a non-empty lowercase string of length up to 2000.
    inf.readLine("[a-z]{1,2000}", "S");
    inf.readLine("[a-z]{1,2000}", "A");
    inf.readLine("[a-z]{1,2000}", "B");

    // No extra content allowed.
    inf.readEof();
    return 0;
}
