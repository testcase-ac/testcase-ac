#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of strings
    int N = inf.readInt(1, 2000000, "N");
    inf.readEoln();

    // Total characters counter
    long long totalChars = 0;

    // Read each string, validate uppercase and count length
    for (int i = 0; i < N; i++) {
        // Each line must be a non-empty string of uppercase letters
        string s = inf.readLine("[A-Z]+", "x_i");
        totalChars += (int)s.size();
        ensuref(totalChars < 2000000LL,
                "Total number of characters (%lld) must be less than 2000000", totalChars);
    }

    // No extra data
    inf.readEof();
    return 0;
}
