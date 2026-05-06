#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first string
    string s1 = inf.readLine("[A-Z]{1,50000}", "first string");
    // Ensure no extra whitespace
    ensuref((int)s1.size() >= 1 && (int)s1.size() <= 50000, "First string length out of bounds: %d", (int)s1.size());

    // Read second string
    string s2 = inf.readLine("[A-Z]{1,50000}", "second string");
    ensuref((int)s2.size() >= 1 && (int)s2.size() <= 50000, "Second string length out of bounds: %d", (int)s2.size());

    // Ensure EOF
    inf.readEof();
}
