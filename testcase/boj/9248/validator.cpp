#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the string S: must be non-empty, only lowercase letters, length <= 500000
    string S = inf.readLine("[a-z]{1,500000}", "S");

    // No extra lines or tokens
    inf.readEof();

    return 0;
}
