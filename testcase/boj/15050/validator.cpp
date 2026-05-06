#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single line: the string s
    string s = inf.readLine("[a-z]{1,100000}", "s");

    // No extra whitespace or lines allowed
    inf.readEof();
}
