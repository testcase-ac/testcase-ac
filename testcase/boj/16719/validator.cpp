#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the input line (the string)
    string s = inf.readLine("[A-Z]{1,100}", "s");
    // The regex ensures that s consists only of uppercase letters and is length 1..100

    inf.readEof();
}
