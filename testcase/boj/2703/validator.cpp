#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        // Read encrypted message: uppercase letters and spaces, length up to 100
        // We allow empty message (length 0) up to 100 as per "length ≤ 100"
        string enc = inf.readLine("[A-Z\\ ]{0,100}", "encrypted_message");
        // Validate each character (redundant given regex, but for clarity)
        for (int i = 0; i < (int)enc.size(); i++) {
            char c = enc[i];
            ensuref((c >= 'A' && c <= 'Z') || c == ' ',
                    "Invalid character '%c' in encrypted message at test %d, pos %d", 
                    c, tc, i);
        }

        // Read mapping line: exactly 26 uppercase letters, no duplicates
        string mapstr = inf.readLine("[A-Z]{26}", "mapping");
        ensuref((int)mapstr.size() == 26,
                "Mapping length is %d, expected 26 at test %d", (int)mapstr.size(), tc);

        vector<bool> seen(26, false);
        for (int i = 0; i < 26; i++) {
            char c = mapstr[i];
            ensuref(c >= 'A' && c <= 'Z',
                    "Invalid character '%c' in mapping at test %d, pos %d", 
                    c, tc, i);
            int idx = c - 'A';
            ensuref(!seen[idx],
                    "Duplicate mapping character '%c' in mapping at test %d, pos %d",
                    c, tc, i);
            seen[idx] = true;
        }
    }

    inf.readEof();
    return 0;
}
