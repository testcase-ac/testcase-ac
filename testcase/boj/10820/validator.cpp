#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read up to 100 lines (N strings), each line may contain spaces.
    vector<string> lines;
    for (int i = 0; i < 100; i++) {
        if (inf.eof()) break;
        // Read any characters (except EOL), including spaces
        string s = inf.readLine("[^]*", "line");
        lines.push_back(s);
    }
    int N = lines.size();
    // Validate the number of lines
    ensuref(N >= 1 && N <= 100,
            "Number of lines is %d, but must be between 1 and 100", N);

    // For each line, check length and allowed characters
    for (int i = 0; i < N; i++) {
        const string &s = lines[i];
        ensuref((int)s.size() <= 100,
                "Length of line %d is %d, but must be at most 100",
                i+1, (int)s.size());
        for (int j = 0; j < (int)s.size(); j++) {
            char c = s[j];
            bool ok = (c >= 'a' && c <= 'z')
                   || (c >= 'A' && c <= 'Z')
                   || (c >= '0' && c <= '9')
                   || (c == ' ');
            ensuref(ok,
                    "Invalid character '%c' at line %d position %d; "
                    "only a-z, A-Z, 0-9, and space are allowed",
                    c, i+1, j+1);
        }
    }

    // Ensure no extra data after the N lines
    inf.readEof();
    return 0;
}
