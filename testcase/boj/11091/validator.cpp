#include "testlib.h"
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of sentences
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Allowed punctuation set
    auto is_allowed = [&](char c) {
        if (c >= 'A' && c <= 'Z') return true;
        if (c >= 'a' && c <= 'z') return true;
        if (c >= '0' && c <= '9') return true;
        if (c == ' ') return true;
        // punctuation: . , ? ! ' "
        if (c == '.' || c == ',' || c == '?' || c == '!' || c == '\'' || c == '"')
            return true;
        return false;
    };

    // Read each sentence
    for (int i = 0; i < N; i++) {
        // Read a line of length 1 to 100 (any characters)
        string s = inf.readLine("[^]{1,100}", "sentence");
        // Validate characters
        for (int j = 0; j < (int)s.size(); j++) {
            char c = s[j];
            ensuref(is_allowed(c),
                    "Invalid character '%c' at line %d, position %d", 
                    c, i+1, j+1);
        }
    }

    // No extra content
    inf.readEof();
    return 0;
}
