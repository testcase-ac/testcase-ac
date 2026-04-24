#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single input line: a non-empty word of at most 1,000,000 letters.
    // Must consist only of alphabet letters A-Z or a-z.
    string s = inf.readLine("[A-Za-z]{1,1000000}", "s");
    // End of input: exactly one newline consumed by readLine, now we must have EOF.
    inf.readEof();

    return 0;
}
