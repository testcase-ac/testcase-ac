#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single input line: word with uppercase letters and underscores.
    // Length must be between 1 and 100.
    string s = inf.readLine("[A-Z_]{1,100}", "s");

    // Count underscores and ensure at most 10.
    int underscore_cnt = 0;
    for (char c : s) {
        if (c == '_') underscore_cnt++;
    }
    ensuref(underscore_cnt <= 10,
            "The number of underscores must be at most 10, but found %d", underscore_cnt);

    // No extra content after the line
    inf.readEof();
    return 0;
}
