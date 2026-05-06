#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first string
    string s1 = inf.readLine("[A-Z]{1,7000}", "first string");
    // Read second string
    string s2 = inf.readLine("[A-Z]{1,7000}", "second string");

    // Ensure no extra lines
    inf.readEof();
}
